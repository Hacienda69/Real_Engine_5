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

	fps_Log.reserve(30);
	ms_Log.reserve(30);

	return true;
}

bool ModuleEditor::CleanUp()
{
	fps_Log.clear();
	ms_Log.clear();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}

// Draw functions -------------------------------------------------------------------------------------------------------------------
void ModuleEditor::DrawEditor()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Assets"))
		{
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Objects"))
		{
			ImGui::Text("Hello world!");
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View")) {

			if (ImGui::Button("Toggle Config"))
				showConfig = !showConfig;

			if (ImGui::Button("Toggle Console"))
				showConsole = !showConsole;

			if (ImGui::Button("Toggle Demo"))
				showDemo = !showDemo;

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::CollapsingHeader("About"))
			{
				ImGui::SeparatorText("ABOUT THE ENGINE:");
				ImGui::Text("Real Engine 5 v0.1");
				ImGui::Text("From the acclaimed studio 'Aprobe Motores', formed by the brilliant");
				ImGui::Text("developers Marc Escandell and Daniel Manas, comes 'Real Engine 5',");
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

	if (showConfig) DrawConfiguration();
	if (showConsole) DrawConsole();
	if(showDemo) ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ModuleEditor::DrawConfiguration() 
{
	ImGui::Begin("Configuration", &showConfig);

	ImGui::Text("El chiki chiki se baila asi");

	if(ImGui::CollapsingHeader("Application"))
	{
		int auxFPS = App->targetFPS;
		if (ImGui::SliderInt("Max FPS", &auxFPS, 1, 120))
			App->targetFPS = auxFPS;

		AddFPS(1000 / App->GetDt());
		AddMS(App->GetDt() * 1000);

		char title[25];
		sprintf_s(title, 25, "FrameRate %0.1f", fps_Log[fps_Log.size() - 1]);
		ImGui::PlotHistogram("##FPS Log", &fps_Log[0], fps_Log.size(), 0, title, 0.0f, 50.0f, ImVec2(0.0f, 50.0f));
		
		sprintf_s(title, 25, "Milliseconds %0.1f", ms_Log[ms_Log.size() - 1]);
		ImGui::PlotHistogram("##FPS Log", &ms_Log[0], ms_Log.size(), 0, title, 0.0f, 50.0f, ImVec2(0.0f, 50.0f));
		
	}
	if(ImGui::CollapsingHeader("Window"))
	{
		if(ImGui::Checkbox("Fullscreen", &fullscreen)) {}
		if(ImGui::Checkbox("Resizable", &resizable)) {}
		if(ImGui::Checkbox("Borderless", &borderless)) {}
		if(ImGui::Checkbox("full_desktop", &full_desktop)) {} 
	}
	if(ImGui::CollapsingHeader("Input"))
	{
		
	}
	if(ImGui::CollapsingHeader("Hardware"))
	{

	}

	ImGui::End();
}

void ModuleEditor::DrawConsole()
{
	ImGui::Begin("Console", &showConsole);

	if (ImGui::Button("Clean Log")) 
	{
		//cleanLog = true;
	}

	ImGui::TextUnformatted(outputLog.data());

	ImGui::End();
}

// Auxiliar functions ---------------------------------------------------------------------------------------------------------------
void ModuleEditor::AddFPS(const float aFPS)
{
	fps_Log.push_back(aFPS);

	if (fps_Log.size() >= 30)
	{
		std::vector<float> auxFPS;
		for (int i = 1; i < fps_Log.size(); i++)
			auxFPS.push_back(fps_Log.at(i));

		fps_Log.clear();
		for (int i = 0; i < auxFPS.size(); i++) {
			fps_Log.push_back(auxFPS.at(i));
		}
		auxFPS.clear();
	}
}

void ModuleEditor::AddMS(const float aMS)
{
	ms_Log.push_back(aMS);

	if (ms_Log.size() >= 30)
	{
		std::vector<float> auxFPS;
		for (int i = 1; i < ms_Log.size(); i++)
			auxFPS.push_back(ms_Log.at(i));

		ms_Log.clear();
		for (int i = 0; i < auxFPS.size(); i++) {
			ms_Log.push_back(auxFPS.at(i));
		}
		auxFPS.clear();
	}
}