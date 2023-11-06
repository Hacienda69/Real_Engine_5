#include "GameObject.h"
#include "Component.h"

GameObject::GameObject()
{
	name = "gameObject";
	parent = nullptr;
	status = false;
}

GameObject::GameObject(GameObject* parent)
{
	name = "gameObject";
	this->parent = parent;
	status = false;

	if (parent != nullptr) {
		parent->children.push_back(this);
	}
}

GameObject::~GameObject()
{
	for (int i = 0; i < components.size(); i++)
	{
		delete components[i];
	}
	components.clear();

	if (parent != nullptr) {

		for (int i = 0; i < parent->children.size(); i++)
		{
			if (parent->children[i] == this) {
				parent->children.erase(parent->children.begin() + i);
			}
			break;
		}
	}
	parent = nullptr;

	while (!children.empty())
	{
		delete children[0];
	}
	children.clear();
}

void GameObject::CreateComponent(componentType type)
{
	Component* newComponent = new Component(this);

	newComponent->type = type;
	newComponent->active = true;

	components.push_back(newComponent);

	delete newComponent;
}

void GameObject::DeleteChild(GameObject* child)
{
	for (int i = 0; i < children.size(); i++) {
		if (children[i] == child) {
			children.erase(children.begin() + i);
			child->parent = nullptr;
		}
	}
}

bool GameObject::ChangeParent(GameObject* NewParent)
{
	if (parent != nullptr) {
		if (NewParent->CheckChildOf(this)) return false;

		parent->DeleteChild(this);
	}

	parent = NewParent;
	NewParent->children.push_back(this);

	return true;
}

bool GameObject::CheckChildOf(GameObject* parent)
{
	if (parent->children.empty()) return false;

	for (int i = 0; i < parent->children.size(); i++) {

		if (children[i] == this) return true;

	}
	return false;
}

GameObject* GameObject::GetParent()
{
	return parent;
}

_Geometry* GameObject::GetComponentMesh()
{
	for (int i = 0; i < components.size(); i++) {

		if (components[i]->type == componentType::GEOMETRY)
		{
			return (_Geometry*)components[i];
		}
	}

	return nullptr;
}

//GameObject* GameObject::GetCompMesh()
//{
//	for (int i = 0; i < components.size(); i++) {
//
//		if (components[i]->type == componentType::GEOMETRY)
//		{
//			return (GameObject*)components[i];
//		}
//	}
//
//	return nullptr;
//}