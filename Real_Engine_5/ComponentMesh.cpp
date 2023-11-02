#pragma once
#include "Globals.h"
#include "Application.h"

#include "ComponentMesh.h"

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
void ComponentMesh::LoadFile(std::string Path)
{
	const aiScene* scene = aiImportFile(Path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array

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
		aiReleaseImport(scene);
	}
	else
		LOG("ERROR loading scene %s", Path);
}

// ---------------------------------------------------------------------------
void ComponentMesh::DrawMesh()
{
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i]->DrawMesh();
	}
}

// ---------------------------------------------------------------------------
void Mesh::DrawMesh()
{
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < numIndex; i++)
	{
		glVertex3f(vertex[index[i] * 3], vertex[index[i] * 3 + 1], vertex[index[i] * 3 + 2]);
	}
	glEnd();
}

// ---------------------------------------------------------------------------
bool ComponentMesh::CleanUp()
{
	aiDetachAllLogStreams();
	return true;
}