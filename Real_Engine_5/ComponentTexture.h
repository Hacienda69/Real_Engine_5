#ifndef COMPONENT_TEXTURE_H
#define COMPONENT_TEXTURE_H

#include "DevIL/include/il.h"
#include "DevIL/include/ilu.h"
#include "backends/imgui_impl_opengl3.h"

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "ModuleRenderer3D.h"

using namespace std;


#define NULLTEX_HEIGHT 64
#define NULLTEX_WIDTH 64

class ComponentTexture : public Module
{
public:
	ComponentTexture(Application* app, bool start_enabled = true);
	~ComponentTexture();

	bool Init();

	GLuint GLTexture(GLuint* imgData, GLuint width, GLuint height);
	GLuint LoadTexture(string path);
	void DeleteTexture(GLuint ID);
	GLubyte null_texture[NULLTEX_HEIGHT][NULLTEX_WIDTH][4];

	bool CleanUp();
	
	GLuint textureID = 0;
	string texPath;
};

#endif // COMPONENT_TEXTURE