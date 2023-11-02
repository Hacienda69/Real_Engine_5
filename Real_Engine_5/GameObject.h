#pragma once
#include "Globals.h"
#include "imgui.h"
#include "glmath.h"
#include <vector>
#include <string>

enum class componentType;
class Component;
class _Geometry;

class GameObject
{

public:
	GameObject();
	GameObject(GameObject* parent);
	~GameObject();

	void CreateComponent(componentType type);
	void DeleteChild(GameObject* child);
	bool ChangeParent(GameObject* NewParent);
	bool CheckChildOf(GameObject* parent);

	GameObject* GetParent();
	_Geometry* GetComponentMesh();
	GameObject* GetCompMesh();
	bool status;
	std::string name;
	char string[128] = "GameObject";
	std::vector<Component*> components;
	GameObject* parent;
	std::vector<GameObject*> children;
};