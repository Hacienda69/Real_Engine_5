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

			if (ImGui::Button("Toggle Inspector"))
				showInspector = !showInspector;

			if (ImGui::Button("Toggle Hierachy"))
				showHierarchy = !showHierarchy;

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

	if (showConfig)		 DrawConfiguration();
	if (showInspector)	 DrawInspector();
	if (showConsole)	 DrawConsole();
	if (showHierarchy)	 DrawHierarchy();
	if (showDemo) ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ModuleEditor::DrawInspector()
{
	ImGui::Begin("Inspector", &showInspector);


	ImGui::End();
}

void ModuleEditor::DrawConfiguration() 
{
	ImGui::Begin("Configuration", &showConfig);

	ImGui::Text("El chiki chiki se baila asi");

	if(ImGui::CollapsingHeader("Application"))
	{
		static char s1[128] = "Real Engine 5";
		ImGui::InputText("Engine Name", s1, IM_ARRAYSIZE(s1));
		static char s2[128] = "CITM UPC";
		ImGui::InputText("Organization", s2, IM_ARRAYSIZE(s2));

		int auxFPS = App->targetFPS;
		if (ImGui::SliderInt("Max FPS", &auxFPS, 1, 120))
			App->targetFPS = auxFPS;

		AddFPS(1 / App->GetDt());
		AddMS(1000 * App->GetDt());

		char title[25];
		sprintf_s(title, 25, "FrameRate %0.1f", fps_Log[fps_Log.size() - 1]);
		ImGui::PlotHistogram("##FPS Log", &fps_Log[0], fps_Log.size(), 0, title, 0.0f, 120.0f, ImVec2(300, 100));
		
		sprintf_s(title, 25, "Milliseconds %0.1f", ms_Log[ms_Log.size() - 1]);
		ImGui::PlotHistogram("##FPS Log", &ms_Log[0], ms_Log.size(), 0, title, 0.0f, 50.0f, ImVec2(300, 100));
		
	}
	if(ImGui::CollapsingHeader("Window"))
	{
		if (ImGui::Button("Reset Screen Size")) 
		{ 
			App->window->ScreenWidth = SCREEN_WIDTH * SCREEN_SIZE; 
			App->window->ScreenHeight = SCREEN_HEIGHT * SCREEN_SIZE;
			App->window->SetWindowSize(); 
		}

		ImGui::Checkbox("Keep Screen Proportions", &App->window->keepScreenProportions);

		int new_Width = App->window->ScreenWidth;
		if (ImGui::SliderInt("Screen Width", &new_Width, 64, 3080)) 
		{
			App->window->ScreenWidth = new_Width;
			App->window->SetWindowSize();
		}
		int new_Height = App->window->ScreenHeight;
		if (ImGui::SliderInt("Screen Height", &new_Height, 64, 2160)) 
		{
			App->window->ScreenHeight = new_Height;
			App->window->SetWindowSize();
		}

		if (ImGui::BeginTable("split", 2)) {
			ImGui::TableNextColumn(); if (ImGui::Checkbox("Fullscreen",   &App->window->win_FullScreen))  { LOG("Fullscreen Toggled");   App->window->ToggleFullscreen();  }
			ImGui::TableNextColumn(); if (ImGui::Checkbox("Resizable",    &App->window->win_Resizable))   { LOG("Resizable Toggled");    App->window->ToggleResizable();   }
			ImGui::TableNextColumn(); if (ImGui::Checkbox("Borderless",	  &App->window->win_Borderless))  { LOG("Borderless Toggled");   App->window->ToggleBorderless();  }
			ImGui::TableNextColumn(); if (ImGui::Checkbox("full_desktop", &App->window->win_FullDesktop)) { LOG("Full Desktop Toggled"); App->window->ToggleFullDesktop(); }
			ImGui::EndTable();
		}
	}
	if(ImGui::CollapsingHeader("Input"))
	{
		
	}
	if(ImGui::CollapsingHeader("Hardware"))
	{

	}

	ImGui::End();

}


void ModuleEditor::DrawHierarchy() 
{
	ImGui::Begin("Hierarchy", &showHierarchy);


	ImGui::End();
}

void ModuleEditor::DrawConsole()
{
	ImGui::Begin("Console", &showConsole);

	if (ImGui::Button("Clean Log")) 
	{
		outputLog.clear();
		cleanLog = true;
	}

	if (!cleanLog) ImGui::Text(outputLog.data());
	else
	{
		ImGui::Text(" ");
		cleanLog = false;
	}

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