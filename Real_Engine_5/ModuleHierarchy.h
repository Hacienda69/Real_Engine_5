#pragma once
#ifndef MODULE_HIERARCHY_H
#define MODULE_HIERARCHY_H

#include "Module.h"
#include "Globals.h"
#include "GameObject.h"

class ModuleHierarchy : public Module 
{
public:

	ModuleHierarchy(Application* app, bool start_enabled = true);
	~ModuleHierarchy();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

	void DrawTree(GameObject* go);

	GameObject* selected;
	GameObject* root;

private:
};

#endif // 
