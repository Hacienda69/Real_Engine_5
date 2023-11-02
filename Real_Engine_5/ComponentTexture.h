#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "ModuleRenderer3D.h"
#include "DevIL/include/il.h"
#include "DevIL/include/ilu.h"
#include "backends/imgui_impl_opengl3.h"

using namespace std;

#define CHECKERS_HEIGHT 64
#define CHECKERS_WIDTH 64

class ComponentTexture : public Module
{
public:
	ComponentTexture(Application* app, bool start_enabled = true);
	~ComponentTexture();

	bool Start();

	bool CleanUp();

	GLuint GenTexture(GLuint* imgData, GLuint width, GLuint height);

	GLuint LoadTexture(string path);

	void FreeTexture(GLuint ID);

	GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
	
	GLuint textureID = 0;
	string texPath;
};