#ifndef ComponentMesh_HEADER
#define ComponentMesh_HEADER

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "ModuleRenderer3D.h"

#include <vector>
using namespace std;

#pragma comment (lib, "Assimp/libx86/assimp.lib")

struct Mesh {
	uint indexID = 0;
	uint numIndex = 0;
	uint* index = nullptr;
	uint vertexID = 0;
	uint numVertex = 0;
	float* vertex = nullptr;
	void DrawMesh();
};

class ComponentMesh : public Module
{
public:
	ComponentMesh(Application* app, bool start_enabled = true);
	~ComponentMesh();

	vector<Mesh*> meshes;
	string pathFile;

	bool Start();

	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	void LoadFile(string Path);
	void DrawMesh();

	bool CleanUp();
};

#endif // ComponentMesh