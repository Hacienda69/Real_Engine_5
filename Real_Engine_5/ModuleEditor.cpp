#include "ModuleEditor.h"
//#include "imgui.h"
//#include "backends/imgui_impl_opengl3.h"

ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
{
	return false;
}

void ModuleEditor::DrawEditor()
{
}

bool ModuleEditor::CleanUp()
{
	return false;
}