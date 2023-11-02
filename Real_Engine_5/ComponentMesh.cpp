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
GameObject* ComponentMesh::LoadFile(std::string Path)
{
	const aiScene* scene = aiImportFile(Path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		GameObject* finalObj = ProcessNode(scene, scene->mRootNode, App->hierarchy->roots, Path);

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