#pragma once
#include "Globals.h"
#include "Application.h"

#include "ComponentMesh.h"
#include "ComponentTexture.h"

#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "Glew/include/glew.h"
#include "Primitive.h"

ComponentMesh::ComponentMesh(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ComponentMesh::~ComponentMesh()
{
}

// ---------------------------------------------------------------------------
bool ComponentMesh::Init()
{
	bool ret = true;

	struct aiLogStream stream;

	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream); //stream Assimp!!

	//ya no est� hardcodeado oleeee

	return ret;
}

// ---------------------------------------------------------------------------
GameObject* ComponentMesh::LoadFile(std::string Path)
{
	const aiScene* scene = aiImportFile(Path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		GameObject* finalObj = ProcessNode(scene, scene->mRootNode, App->hierarchy->root, Path);

		aiReleaseImport(scene);

		return finalObj;
	}
	else
		LOG("ERROR WITH SCENE %s", Path);
}

void ComponentMesh::BufferMesh(Mesh* mesh)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glGenBuffers(1, (GLuint*)&(mesh->vertexID));
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->numVertex * VERTEX_ARG, mesh->vertex, GL_STATIC_DRAW);

	glGenBuffers(1, (GLuint*)&(mesh->indexID));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * mesh->numIndex, mesh->index, GL_STATIC_DRAW);

	glDisableClientState(GL_VERTEX_ARRAY);
	meshes.push_back(mesh);
}

// ---------------------------------------------------------------------------
void Mesh::DrawMesh()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, vertexID);

	glVertexPointer(3, GL_FLOAT, sizeof(float) * VERTEX_ARG, NULL);
	glTexCoordPointer(2, GL_FLOAT, sizeof(float) * VERTEX_ARG, (void*)(sizeof(float) * 3));

	glBindTexture(GL_TEXTURE_2D, id_texture);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);

	glPushMatrix();

	if (Parent != nullptr) {
		//glMultMatrixf(Parent->transform->GetTransformMatrix().ptr());
	}

	glDrawElements(GL_TRIANGLES, numIndex, GL_UNSIGNED_INT, NULL);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_COORD_ARRAY);
}

// ---------------------------------------------------------------------------
bool ComponentMesh::CleanUp()
{
	for (int i = 0; i < meshes.size(); i++) {
		delete meshes[i];
		meshes[i] = nullptr;
	}
	meshes.clear();

	aiDetachAllLogStreams();
	return true;
}

GameObject* ProcessNode(const aiScene* scene, aiNode* node, GameObject* parent, string Path)
{
	if (node->mNumMeshes == 0 && node->mNumChildren == 0) return nullptr;

	GameObject* gObj = new GameObject(parent);

	gObj->name = node->mName.C_Str();


	aiMatrix4x4 TransformMat = node->mTransformation;

	aiVector3D scale, position, rotation;
	aiQuaternion QuatRotation;

	TransformMat.Decompose(scale, QuatRotation, position);
	rotation = QuatRotation.GetEuler();

	gObj->transform->scale = float3(scale.x, scale.y, scale.z);
	gObj->transform->position = float3(position.x, position.y, position.z);
	gObj->transform->rotation = float3(rotation.x * RADTODEG, rotation.y * RADTODEG, rotation.z * RADTODEG);
	gObj->transform->SetTransformMatrix();

	if (node->mNumMeshes != 0) {

		CMesh* component = new CMesh(gObj);


		string texture_path = "";


		for (int i = 0; i < node->mNumMeshes; i++)
		{
			Mesh* mesh = ImportMesh(scene->mMeshes[node->mMeshes[i]]);

			if (mesh == nullptr) {
				LOG("Error loading scene %s", Path);
				continue;
			}

			mesh->Owner = gObj;
			component->meshes.push_back(mesh);

			if (texture_path == "") texture_path = ImportTexture(scene, node->mMeshes[i], Path);

		}

		gObj->components.push_back(component);
		gObj->fixed = true;



		if (texture_path != "") {
			CTexture* componentT = new CTexture(gObj);
			gObj->components.push_back(componentT);
			componentT->LinkTexture(texture_path);
		}
	}

	for (int i = 0; i < node->mNumChildren; i++) {
		ProcessNode(scene, node->mChildren[i], gObj, Path);
	}

	return gObj;
}