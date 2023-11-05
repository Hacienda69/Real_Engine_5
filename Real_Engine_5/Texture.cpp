#include "Application.h"
#include "Texture.h"
#include "Geometry.h"
#include "GameObject.h"
#include "ComponentMesh.h"


Textureclass::Textureclass() : Component(nullptr)
{
	type = componentType::TEXTURE;
	Parent = nullptr;
}

Textureclass::Textureclass(GameObject* Parent) : Component(Parent)
{
	type = componentType::TEXTURE;
	this->Parent = Parent;
}

Textureclass::~Textureclass()
{

}

void Textureclass::TexturePath(std::string path)
{
	if (textureID != 0)
	{
		Application::GetApp()->tex->DeleteTexture(textureID);
	}
	textureID = Application::GetApp()->tex->LoadTexture(path);

	RefreshTexture();
}

void Textureclass::RefreshTexture()
{
	_Geometry* rt = Parent->GetComponentMesh();
	if (rt == nullptr) return;

	//for(int i = 0; i < rt->meshes)
	uint text = 0;

	if (IsLoaded) {
		text = textureID;
	}
	else {
		text = Application::GetApp()->tex->textureID;
	}

	for (int i = 0; i < rt->meshes.size(); i++)
	{
		rt->meshes[i]->id_texture = text;
	}

}

void Textureclass::Inspector()
{
	if (ImGui::CollapsingHeader("Texture"))
	{
		ImGui::Checkbox("Loaded Texture\t", &IsLoaded);
	}
	RefreshTexture();

	ImGui::NewLine();
	ImGui::Separator();
	ImGui::NewLine();
}