#include "Application.h"
#include "Geometry.h"
#include "GameObject.h"
#include "ComponentMesh.h"


_Geometry::_Geometry() : Component(nullptr)
{
	type = componentType::GEOMETRY;
	meshType = MeshType::FBX;
	Parent = nullptr;
}

_Geometry::_Geometry(GameObject* Parent) : Component(Parent)
{
	type = componentType::GEOMETRY;
	meshType = MeshType::FBX;
	this->Parent = Parent;
}

_Geometry::_Geometry(GameObject* owner, MeshType _meshType) : Component(owner)
{
	type = componentType::GEOMETRY;
	meshType = _meshType;
	this->Parent = owner;
}

_Geometry::~_Geometry()
{
}