#pragma once
#include "Globals.h"
#include "Component.h"
#include "imgui.h"

#include<string>

class GameObject;
class Component;

class Textureclass : public Component
{
public:
	Textureclass();
	Textureclass(GameObject* Parent);
	~Textureclass();

	GLuint textureID = 0;
	bool IsLoaded = true;

	void TexturePath(std::string path);
	void RefreshTexture();
	void Inspector();
};
