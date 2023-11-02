#include "ModuleHierarchy.h"
#include "Application.h"
#include "ModuleEditor.h"

#include "ModuleRenderer3D.h"
#include "glew.h"

ModuleHierarchy::ModuleHierarchy(Application* app, bool start_enabled = true) : Module(app, start_enabled)
{

}

ModuleHierarchy::~ModuleHierarchy() 
{

}

// Application functions ---------------------------------------------------
bool ModuleHierarchy::Init() 
{
	return true;
}

update_status ModuleHierarchy::Update(float dt) 
{

}

bool ModuleHierarchy::CleanUp() 
{
	return true;
}