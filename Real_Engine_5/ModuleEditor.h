#ifndef MODULE_EDITOR
#define MODULE_EDITOR

#include "Module.h"
#include "Globals.h"

#include <vector>

class ModuleEditor : public Module
{
public:

	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	//update_status PreUpdate(float dt) override; NO (?)

	bool Init() override;
	bool CleanUp() override;

	void DrawEditor();
	void DrawConfiguration();
	void DrawConsole();

	void AddFPS(const float aFPS);
	void AddMS(const float aMS);

public:

	std::vector<float> fps_Log;
	std::vector<float> ms_Log;

	bool cleanLog = false;

private:
	bool showDemo = false;
	bool showConfig = false;
	bool showConsole = false;

	bool fullscreen = false;
	bool resizable = false;
	bool borderless = false;
	bool full_desktop = false;

};

#endif //MODULE_EDITOR