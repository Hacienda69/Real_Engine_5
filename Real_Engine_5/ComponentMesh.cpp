#pragma once
#include "Globals.h"
#include "Application.h"
#include "Geometry.h"
#include "Texture.h"
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
void Mesh::InnitAABB() {
	float* vertices_positions = new float[numVertex * 3];
	for (size_t i = 0; i < numVertex; i++)
	{
		vertices_positions[i * 3] = vertex[i * VERTEX_ARG];
		vertices_positions[i * 3 + 1] = vertex[i * VERTEX_ARG + 1];
		vertices_positions[i * 3 + 2] = vertex[i * VERTEX_ARG + 2];
	}

	localAABB.SetNegativeInfinity();
	localAABB.Enclose((float3*)vertices_positions, numVertex);
	delete[] vertices_positions;
}

// ---------------------------------------------------------------------------
bool ComponentMesh::Init()
{
	bool ret = true;

	struct aiLogStream stream;

	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream); //stream Assimp!!

	//ya no está hardcodeado oleeee

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
Mesh* ComponentMesh::ImportMesh(aiMesh* aiMesh)
{
	Mesh* mesh = new Mesh();

	mesh->numVertex = aiMesh->mNumVertices;
	mesh->vertex = new float[mesh->numVertex * VERTEX_ARG];

	for (int k = 0; k < mesh->numVertex; k++) {

		mesh->vertex[k * VERTEX_ARG] = aiMesh->mVertices[k].x;
		mesh->vertex[k * VERTEX_ARG + 1] = aiMesh->mVertices[k].y;
		mesh->vertex[k * VERTEX_ARG + 2] = aiMesh->mVertices[k].z;

		if (aiMesh->mTextureCoords[0] == nullptr) continue;
		mesh->vertex[k * VERTEX_ARG + 3] = aiMesh->mTextureCoords[0][k].x;
		mesh->vertex[k * VERTEX_ARG + 4] = aiMesh->mTextureCoords[0][k].y;
	}
	if (aiMesh->HasFaces())
	{
		mesh->numIndex = aiMesh->mNumFaces * 3;
		mesh->index = new uint[mesh->numIndex];

		for (uint j = 0; j < aiMesh->mNumFaces; j++)
		{
			if (aiMesh->mFaces[j].mNumIndices != 3) {
				LOG("WARNING, geometry face with != 3 indices!");
			}
			else
			{
				memcpy(&mesh->index[j * 3], aiMesh->mFaces[j].mIndices, 3 * sizeof(uint));
			}
		}
		mesh->InnitAABB();

		BufferMesh(mesh);

		return mesh;
	}
	else {

		delete mesh;

		return nullptr;
	}

}

string ComponentMesh::ImportTexture(const aiScene* scene, int index, string path)
{
	if (scene->HasMaterials())
	{
		aiMaterial* MaterialIndex = scene->mMaterials[scene->mMeshes[index]->mMaterialIndex];
		if (MaterialIndex->GetTextureCount(aiTextureType_DIFFUSE) > 0) {

			aiString TextPath;
			MaterialIndex->GetTexture(aiTextureType_DIFFUSE, 0, &TextPath);

			for (int i = 0; i < path.size(); i++)
			{
				if (path[i] == '\\')
				{
					path[i] = '/';
				}
			}

			string NormTextPath = TextPath.C_Str();

			for (int i = 0; i < NormTextPath.size(); i++)
			{
				if (NormTextPath[i] == '\\')
				{
					NormTextPath[i] = '/';
				}
			}

			string AssetsPath = path;
			uint AssetsPos = AssetsPath.find("Assets/");

			AssetsPath = AssetsPath.substr(AssetsPos, AssetsPath.find_last_of("/") - AssetsPos);
			AssetsPath.append("/").append(TextPath.C_Str());

			return AssetsPath;
		}
	}

	return "";
}

GameObject* ComponentMesh::ProcessNode(const aiScene* scene, aiNode* node, GameObject* parent, string Path)
{

	if (node->mNumMeshes == 0 && node->mNumChildren == 0) return nullptr;

	GameObject* gObj = new GameObject(parent);

	gObj->name = node->mName.C_Str();

	if (node->mNumMeshes != 0) {

		_Geometry* component = new _Geometry(gObj);

		string texture_path = "";

		for (int i = 0; i < node->mNumMeshes; i++)
		{
			Mesh* mesh = ImportMesh(scene->mMeshes[node->mMeshes[i]]);

			if (mesh == nullptr) {
				LOG("Error loading scene %s", Path);
				continue;
			}

			mesh->Parent = gObj;
			component->meshes.push_back(mesh);

			if (texture_path == "") texture_path = ImportTexture(scene, node->mMeshes[i], Path);

		}

		gObj->components.push_back(component);
		gObj->status = true;

		if (texture_path != "") {
			Textureclass* componentT = new Textureclass(gObj);
			gObj->components.push_back(componentT);
			componentT->TexturePath(texture_path);
		}
	}

	for (int i = 0; i < node->mNumChildren; i++) {
		ProcessNode(scene, node->mChildren[i], gObj, Path);
	}

	return gObj;
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