#pragma once
#include "Globals.h"
#include "Application.h"
#include "ComponentTexture.h"

ComponentTexture::ComponentTexture(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ComponentTexture::~ComponentTexture()
{
}

bool ComponentTexture::Init()
{
	for (int i = 0; i < NULLTEX_HEIGHT; i++) {
		for (int j = 0; j < NULLTEX_WIDTH; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			null_texture[i][j][0] = (GLubyte)c;
			null_texture[i][j][1] = (GLubyte)c;
			null_texture[i][j][2] = (GLubyte)c;
			null_texture[i][j][3] = (GLubyte)255;
		}
	}

	glEnable(GL_TEXTURE_2D);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, NULLTEX_WIDTH, NULLTEX_HEIGHT,
		0, GL_RGBA, GL_UNSIGNED_BYTE, null_texture);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glClearColor(0.f, 0.f, 0.f, 1.f);

	ilInit();
	ilClearColour(255, 255, 255, 000);

	return true;
}

GLuint ComponentTexture::GLTexture(GLuint* imgData, GLuint width, GLuint height)
{
	GLuint TextID = 0;

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &TextID);
	glBindTexture(GL_TEXTURE_2D, TextID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	return TextID;
}

GLuint ComponentTexture::LoadTexture(string path)
{
	GLuint TextID = 0;
	ILuint imgID = 0;
	ilGenImages(1, &imgID);
	ilBindImage(imgID);

	ILboolean success = ilLoadImage(path.c_str());

	if (path.substr(path.find_last_of(".") + 1) == "png")
	{
		iluFlipImage();
	}

	if (success == IL_TRUE)
	{
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		if (success == IL_TRUE)
		{
			TextID = GLTexture((GLuint*)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
		}
		ilDeleteImages(1, &imgID);

		if (TextID == 0)
		{
			printf("CANNOT LOAD %s\n", path.c_str());
		}
	}
	return TextID;
}

void ComponentTexture::DeleteTexture(GLuint ID)
{
	if (ID != 0)
	{
		glDeleteTextures(1, &ID);
		ID = 0;
	}
}

bool ComponentTexture::CleanUp()
{
	return true;
}