#pragma once

class GameObject;

enum class componentType
{
	NONE,
	GEOMETRY,
	TEXTURE,
};

class Component
{
public:
	Component::Component(GameObject* owner)
	{
		type = componentType::NONE;
		active = true;
		this->Parent = owner;
	}

	virtual ~Component();

	virtual void Inspector();

	componentType type;
	bool active;
	GameObject* Parent;
};