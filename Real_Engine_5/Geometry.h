#pragma once
#include "Globals.h"
#include "Component.h"
#include "imgui.h"
#include "Primitive.h"

#include <vector>

class GameObject;
class Component;
struct Mesh;

enum class MeshType
{
	FBX,
	CUBE,
	SPHERE,
	CYLINDER,
	LINE,
	PLANE,
};

class _Geometry : public Component
{
public:

	_Geometry();
	_Geometry(GameObject* owner);
	_Geometry(GameObject* owner, MeshType _meshType);
	~_Geometry();

	MeshType meshType;

	//Mesh* mesh;

	std::vector<Mesh*> meshes;

	Primitive* GObjPrim;
};