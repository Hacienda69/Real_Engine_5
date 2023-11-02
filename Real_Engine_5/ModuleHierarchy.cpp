#include "ModuleHierarchy.h"
#include "Application.h"
#include "ModuleEditor.h"

#include "ModuleRenderer3D.h"
#include "glew.h"

ModuleHierarchy::ModuleHierarchy(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	selected = nullptr;
	root = nullptr;
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
	return UPDATE_CONTINUE;
}

bool ModuleHierarchy::CleanUp() 
{
	return true;
}

// Tree Manager ------------------------------------------------------------
void ModuleHierarchy::DrawTree(GameObject* obj)
{
	int treeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
	int childFlags = treeFlags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

	GameObject* targetChild = nullptr;
	int numChilds = obj->children.size();

	for (int i = 0; i < numChilds; i++) 
	{
		targetChild = obj->children[i];

		bool clown = ImGui::TreeNodeEx((void*)(intptr_t)i, treeFlags, targetChild->name.c_str());

		if(selected == obj) {}

		if (targetChild->children.size() > 0) 
		{
			if (ImGui::IsItemClicked()) {
				if (selected == targetChild) selected = root;
				else selected = targetChild;
			}
			if (clown) 
			{
				DrawTree(targetChild);
			}
		}
		else
		{
			ImGui::TreeNodeEx((void*)(intptr_t)i, childFlags, targetChild->name.c_str());

			if (ImGui::IsItemClicked()) {
				if (selected == targetChild) selected = root;
				else selected = targetChild;
			}
		}

	}

}