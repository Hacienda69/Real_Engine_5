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
	void DrawInspector();
	void DrawConfiguration();
	void DrawConsole();
	void DrawHierarchy();

	void AddFPS(const float aFPS);
	void AddMS(const float aMS);

public:

	std::vector<float> fps_Log;
	std::vector<float> ms_Log;

	bool cleanLog = false;

private:
	bool showDemo = false;
	bool showInspector = false;
	bool showConfig = false;
	bool showConsole = false;
	bool showHierarchy = false;
};

#endif //MODULE_EDITOR