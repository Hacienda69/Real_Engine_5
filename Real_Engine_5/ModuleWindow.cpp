#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	window = NULL;
	screen_surface = NULL;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{

	LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		ScreenWidth = SCREEN_WIDTH * SCREEN_SIZE;
		ScreenHeight = SCREEN_HEIGHT * SCREEN_SIZE;

		defScreenProportion = ScreenHeight / ScreenWidth;

		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		if(win_FullScreen == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if(win_Resizable == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		if(win_Borderless == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if(win_FullDesktop == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, flags);
		

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();

	return true;
}

void ModuleWindow::SetTitle(const char* title)
{
	SDL_SetWindowTitle(window, title);
}

void ModuleWindow::ToggleFullscreen()
{
	Uint32 flags = SDL_GetWindowFlags(window);
	if (flags & SDL_WINDOW_FULLSCREEN) {
		SDL_SetWindowFullscreen(window, 0);  // Cambiar a modo de ventana normal
	}
	else {
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);  // Cambiar a pantalla completa
	}
}

void ModuleWindow::ToggleBorderless()
{
	Uint32 flags = SDL_GetWindowFlags(window);
	if (flags & SDL_WINDOW_BORDERLESS) {
		SDL_SetWindowBordered(window, SDL_TRUE);  // Activar los bordes de la ventana
	}
	else {
		SDL_SetWindowBordered(window, SDL_FALSE);  // Desactivar los bordes de la ventana
	}
}

void ModuleWindow::ToggleResizable()
{
	Uint32 flags = SDL_GetWindowFlags(window);
	if (flags & SDL_WINDOW_RESIZABLE) {
		SDL_SetWindowResizable(window, SDL_FALSE);  // Hacer la ventana no redimensionable
	}
	else {
		SDL_SetWindowResizable(window, SDL_TRUE);  // Hacer la ventana redimensionable
	}
}

void ModuleWindow::ToggleFullDesktop()
{
	Uint32 flags = SDL_GetWindowFlags(window);
	if (flags & SDL_WINDOW_FULLSCREEN_DESKTOP) {
		SDL_SetWindowFullscreen(window, 0);  // Cambiar a modo de ventana normal
	}
	else {
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);  // Cambiar a escritorio completo
	}
}

void ModuleWindow::SetWindowSize() 
{
	LOG("Changing Window Size");

	//opOrder = true: ScreenHeight = ScreenWidth * proportion, opOrder = false: ScreenWidth = ScreenHeight * proportion
	if (keepScreenProportions) 
	{
		ScreenHeight = ScreenWidth * 0.5652f;
	}

	SDL_SetWindowSize(window, ScreenWidth, ScreenHeight);
}