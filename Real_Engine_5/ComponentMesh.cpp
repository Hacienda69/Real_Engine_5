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
bool ComponentMesh::Start()
{
	bool ret = true;

	struct aiLogStream stream;

	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream); //stream Assimp!!

	//ya no está hardcodeado oleeee

	return ret;
}

// ---------------------------------------------------------------------------
update_status ComponentMesh::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------------------------
update_status ComponentMesh::Update(float dt)
{
	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------------------------
update_status ComponentMesh::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------------------------
<<<<<<< Updated upstream
void ComponentMesh::LoadFile(const std::string Path)
=======
GameObject* ComponentMesh::LoadFile(std::string Path)
>>>>>>> Stashed changes
{
	const aiScene* scene = aiImportFile(Path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
<<<<<<< Updated upstream
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			Mesh* mesh = new Mesh();

			mesh->numVertex = scene->mMeshes[i]->mNumVertices;
			mesh->vertex = new float[mesh->numVertex * 3];
			
			memcpy(mesh->vertex, scene->mMeshes[i]->mVertices, sizeof(float) * mesh->numVertex * 3);

			if (scene->mMeshes[i]->HasFaces())
			{
				mesh->numIndex = scene->mMeshes[i]->mNumFaces * 3;
				mesh->index = new uint[mesh->numIndex];
				for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
				{
					if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3) {
						LOG("WARNING, geometry face with != 3 index!");
					}
					else
						memcpy(&mesh->index[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));

				}
				meshes.push_back(mesh);
			}
			else
				delete mesh;
		}
=======
		GameObject* finalObj = ProcessNode(scene, scene->mRootNode, App->hierarchy->roots, Path);

>>>>>>> Stashed changes
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
		glMultMatrixf(Parent->transform->GetTransformMatrix().ptr());
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