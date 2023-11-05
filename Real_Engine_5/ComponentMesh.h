#ifndef COMPONENT_MESH_H
#define COMPONENT_MESH_H

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "ModuleRenderer3D.h"
#include "MathGeoLib/include/MathGeoLib.h"

#include <vector>
using namespace std;

#pragma comment (lib, "Assimp/libx86/assimp.lib")

#define VERTEX_ARG 5

class GameObject;

struct Mesh {
	uint indexID = 0;
	uint numIndex = 0;
	uint* index = nullptr;
	uint vertexID = 0;
	uint numVertex = 0;
	float* vertex = nullptr;
	GLuint id_texture = 0;
	GameObject* Parent;
	AABB localAABB;
	void InnitAABB();
	void DrawMesh();
};

class ComponentMesh : public Module
{
public:
	ComponentMesh(Application* app, bool start_enabled = true);
	~ComponentMesh();

	vector<Mesh*> meshes;
	string pathFile = "";

	bool Init();

	GameObject* LoadFile(string Path);
	bool CleanUp();

	void BufferMesh(Mesh* mesh);

private:
	Mesh* ImportMesh(aiMesh* aiMesh);
	string ImportTexture(const aiScene* scene, int index, string path);
	GameObject* ProcessNode(const aiScene* scene, aiNode* node, GameObject* parent, string Path);
};

#endif // COMPONENT_MESH