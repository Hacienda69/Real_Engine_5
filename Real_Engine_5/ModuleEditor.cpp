#include "ModuleEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleHierarchy.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

#include "Assimp/include/version.h"

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

	RAM = SDL_GetSystemRAM();
	CPU = SDL_GetCPUCount();
	CACHE = SDL_GetCPUCacheLineSize();

	PLATFORM = SDL_GetPlatform();
	NUM_MONITORS = SDL_GetNumVideoDisplays();

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
		if (ImGui::BeginMenu("GameObject"))
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

				ImGui::NewLine();
				
				ImGui::SeparatorText("ABOUT THE AUTHORS:");
				ImGui::BulletText("Marc Escandell Alonso");

				if (ImGui::MenuItem("	Marc's Github: https://github.com/MrMonkey420"))
						ShellExecute(NULL, "OPEN", "https://github.com/MrMonkey420", NULL, NULL, SW_SHOW);

				ImGui::NewLine();

				ImGui::BulletText("Daniel Manas Calvo");

				if (ImGui::MenuItem("	Dani's Github: https://github.com/Hacienda69"))
					ShellExecute(NULL, "OPEN", "https://github.com/Hacienda69", NULL, NULL, SW_SHOW);

				ImGui::NewLine();

				ImGui::SeparatorText("3RD PARTY LIBRARIES USED:");

				ImGui::BulletText("SDL 2.0.4");
				if (ImGui::MenuItem("	SDL: https://www.libsdl.org/"))
					ShellExecute(NULL, "OPEN", "https://www.libsdl.org/", NULL, NULL, SW_SHOW);

				ImGui::BulletText("ImGui 1.90 WIP");
				if (ImGui::MenuItem("	ImGui: https://github.com/ocornut/imgui/tree/docking"))
					ShellExecute(NULL, "OPEN", "https://github.com/ocornut/imgui/tree/docking", NULL, NULL, SW_SHOW);

				ImGui::BulletText("Glew 2.1.0");
				if (ImGui::MenuItem("	Glew: https://glew.sourceforge.net/"))
					ShellExecute(NULL, "OPEN", "https://glew.sourceforge.net/", NULL, NULL, SW_SHOW);

				ImGui::BulletText("MathGeoLib 1.0");
				if (ImGui::MenuItem("	MathGeoLib: https://github.com/juj/MathGeoLib"))
					ShellExecute(NULL, "OPEN", "https://github.com/juj/MathGeoLib", NULL, NULL, SW_SHOW);

				ImGui::BulletText("OpenGL %s", glGetString(GL_VERSION));
				if (ImGui::MenuItem("	OpenGL: https://www.opengl.org/"))
					ShellExecute(NULL, "OPEN", "https://www.opengl.org/", NULL, NULL, SW_SHOW);

				ImGui::BulletText("Assimp %d.%d.%d", aiGetVersionMajor(), aiGetVersionMinor(), aiGetVersionRevision());
				if (ImGui::MenuItem("	Assimp: https://assimp.org/"))
					ShellExecute(NULL, "OPEN", "https://assimp.org/", NULL, NULL, SW_SHOW);

				ImGui::BulletText("PhysFS 3.0.2");
				if (ImGui::MenuItem("	PhysFS: https://icculus.org/physfs/"))
					ShellExecute(NULL, "OPEN", "https://icculus.org/physfs/", NULL, NULL, SW_SHOW);

				ImGui::BulletText("DevIL 1.8.0");
				if (ImGui::MenuItem("	DevIL: https://github.com/DentonW/DevIL"))
					ShellExecute(NULL, "OPEN", "https://github.com/DentonW/DevIL", NULL, NULL, SW_SHOW);

				ImGui::NewLine();

				ImGui::SeparatorText("lICENSE");

				ImGui::NewLine();

				ImGui::Text("MIT License");

				ImGui::NewLine();

				ImGui::Text("Copyright(c) 2023 Hacienda69");

				ImGui::NewLine();

				ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy");
				ImGui::Text("of this software and associated documentation files(the 'Software'), to deal");
				ImGui::Text("in the Software without restriction, including without limitation the rights");
				ImGui::Text("to use, copy, modify, merge, publish, distribute, sublicense, and /or sell");
				ImGui::Text("copies of the Software, and to permit persons to whom the Software is");
				ImGui::Text("furnished to do so, subject to the following conditions :");

				ImGui::NewLine();

				ImGui::Text("The above copyright notice and this permission notice shall be included in");
				ImGui::Text("all copies or substantial portions of the Software.");

				ImGui::NewLine();

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

		ImGui::Separator();

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
		
		ImGui::Separator();

		ImGui::Text("Average MS: %.3f", 1000.0 / ImGui::GetIO().Framerate);
		ImGui::Text("Average FPS: %.1f", ImGui::GetIO().Framerate);

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

		ImGui::Separator();

		if (ImGui::BeginTable("split", 2)) {
			ImGui::TableNextColumn(); if (ImGui::Checkbox("Fullscreen",   &App->window->win_FullScreen))  { LOG("Fullscreen Toggled");   App->window->ToggleFullscreen();  }
			ImGui::TableNextColumn(); if (ImGui::Checkbox("Resizable",    &App->window->win_Resizable))   { LOG("Resizable Toggled");    App->window->ToggleResizable();   }
			ImGui::TableNextColumn(); if (ImGui::Checkbox("Borderless",	  &App->window->win_Borderless))  { LOG("Borderless Toggled");   App->window->ToggleBorderless();  }
			ImGui::TableNextColumn(); if (ImGui::Checkbox("full_desktop", &App->window->win_FullDesktop)) { LOG("Full Desktop Toggled"); App->window->ToggleFullDesktop(); }
			ImGui::EndTable();
		}
	}
	if(ImGui::CollapsingHeader("Inputs"))
	{
		ImGuiIO io = ImGui::GetIO();

		ImGui::Text("Mouse Position:"); ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "%g, %g", io.MousePos.x, io.MousePos.y);
		ImGui::Text("Mouse Delta:"); ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "%g, %g", io.MouseDelta.x, io.MouseDelta.y);
		ImGui::Text("Mouse Wheel:", io.MouseWheel);

		struct funcs { static bool IsLegacyNativeDupe(ImGuiKey key) { return key < 512 && ImGui::GetIO().KeyMap[key] != -1; } }; // Hide Native<>ImGuiKey duplicates when both exists in the array
		ImGuiKey start_key = (ImGuiKey)0;

		ImGui::Text("Keys down:");
		for (ImGuiKey key = start_key; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) 
		{ 
			if (funcs::IsLegacyNativeDupe(key) || !ImGui::IsKeyDown(key)) continue; ImGui::SameLine(); 
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), (key < ImGuiKey_NamedKey_BEGIN) ? "\"%s\"" : "\"%s\" %d", ImGui::GetKeyName(key), key); 
		}
	}
	if(ImGui::CollapsingHeader("Hardware"))
	{
		ImGui::Text("Platform: "); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), PLATFORM.c_str());

		ImGui::Separator();

		ImGui::Text("RAM: ");   ImGui::SameLine(); ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "%d", RAM);
		ImGui::Text("CPU: ");   ImGui::SameLine(); ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "%d", CPU);
		ImGui::Text("GPU: ");   ImGui::SameLine(); ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "%s", glGetString(GL_VENDOR));
		ImGui::Text("Cache: "); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "%d", CACHE);

		ImGui::Separator();

		ImGui::Text("Display number: "); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "%d", NUM_MONITORS);
	}

	ImGui::End();

}

void ModuleEditor::DrawHierarchy() 
{
	ImGui::Begin("Hierarchy", &showHierarchy);

	App->hierarchy->DrawTree(App->hierarchy->root);

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