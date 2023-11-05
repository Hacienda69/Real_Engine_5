#pragma once

#include "Globals.h"
#include "Timer.h"

#include "Module.h"
#include "ModuleCamera3D.h"
#include "ModuleEditor.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleHierarchy.h"
#include "ModuleWindow.h"

#include "ComponentMesh.h"
#include "ComponentTexture.h"

#include <vector>

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleRenderer3D;
class ModuleCamera3D;
class ModuleHierarchy;
class ModuleEditor;

class ComponentMesh;
class ComponentTexture;

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleHierarchy* hierarchy;
	ModuleEditor* editor;

	ComponentMesh* mesh;
	ComponentTexture* tex;

	float targetFPS = 60;

	float	dt;

private:

	Timer	ms_timer;
	std::vector<Module*> list_modules;

public:

	Application();
	~Application();

	static Application* GetApp();

	bool Init();
	update_status Update();
	bool CleanUp();

	float GetDt();

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

extern Application* externalapp;