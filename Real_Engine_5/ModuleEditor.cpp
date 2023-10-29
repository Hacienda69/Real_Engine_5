#include "ModuleEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL3_Init();

	mFPSLog.reserve(30);

	return true;
}

void ModuleEditor::DrawEditor()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::Text("Hello world!");
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Assets"))
		{
			ImGui::Text("Hello world!");
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Objects"))
		{
			ImGui::Text("Hello world!");
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			ImGui::Text("Hello world!");

			if (ImGui::CollapsingHeader("About"))
			{
				ImGui::SeparatorText("ABOUT THE ENGINE:");
				ImGui::Text("Real Engine 5 v0.1");
				ImGui::Text("From the acclaimed studio 'Aprobe Motores', formed by the brilliant");
				ImGui::Text("developers Marc Escandell and Daniel Mañas, comes 'Real Engine 5',");
				ImGui::Text("a new cutting - edge video game engine in the thriving virtual");
				ImGui::Text("entertainment industry, we hope you enjoy it.");

				ImGui::Text(" ");
				
				ImGui::SeparatorText("ABOUT THE AUTHORS:");
				ImGui::BulletText("Marc Escandell Alonso");

				if (ImGui::MenuItem("	Marc's Github: https://github.com/MrMonkey420"))
						ShellExecute(NULL, "OPEN", "https://github.com/MrMonkey420", NULL, NULL, SW_SHOW);

				ImGui::Text(" ");

				ImGui::BulletText("Daniel Manas Calvo");

				if (ImGui::MenuItem("	Dani's Github: https://github.com/Hacienda69"))
					ShellExecute(NULL, "OPEN", "https://github.com/Hacienda69", NULL, NULL, SW_SHOW);

				ImGui::Text(" ");

				ImGui::SeparatorText("3RD PARTY LIBRARIES USED:");
				ImGui::Text("con las versiones y links a sus webs");

				ImGui::Text(" ");

				ImGui::SeparatorText("lICENSE");

				ImGui::Text(" ");

				ImGui::Text("MIT License");

				ImGui::Text(" ");

				ImGui::Text("Copyright(c) 2023 Hacienda69");

				ImGui::Text(" ");

				ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy");
				ImGui::Text("of this software and associated documentation files(the 'Software'), to deal");
				ImGui::Text("in the Software without restriction, including without limitation the rights");
				ImGui::Text("to use, copy, modify, merge, publish, distribute, sublicense, and /or sell");
				ImGui::Text("copies of the Software, and to permit persons to whom the Software is");
				ImGui::Text("furnished to do so, subject to the following conditions :");

				ImGui::Text(" ");

				ImGui::Text("The above copyright notice and this permission notice shall be included in");
				ImGui::Text("all copies or substantial portions of the Software.");

				ImGui::Text(" ");

				ImGui::Text("THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR");
				ImGui::Text("IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,");
				ImGui::Text("FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE");
				ImGui::Text("AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER");
				ImGui::Text("LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,");
				ImGui::Text("OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE");
				ImGui::Text("SOFTWARE.");
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool ModuleEditor::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}

void ModuleEditor::AddFPS(const float aFPS)
{
	if (mFPSLog.size() < 30)
	{
		mFPSLog.push_back(aFPS);
	}
	else
	{
		for (unsigned int i = 0; i < mFPSLog.size(); i++)
		{
			if (i + 1 < mFPSLog.size())
			{
				float iCopy = mFPSLog[i + 1];
				mFPSLog[i] = iCopy;
			}
		}
		mFPSLog[mFPSLog.capacity() - 1] = aFPS;
	}
}