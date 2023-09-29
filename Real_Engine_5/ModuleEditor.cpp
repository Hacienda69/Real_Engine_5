#include "ModuleEditor.h"


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