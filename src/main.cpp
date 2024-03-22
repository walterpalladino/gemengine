#include <iostream>
#include <fstream> // File io header

#include "core/GemEngine.h"
#include "utils/Log.h"
#include "utils/StringUtils.h"
#include "core/Config.h"
#include "core/scenes/SceneManager.h"
#include "app/Scene1.h"
#include "app/Scene2.h"
#include "app/Scene3.h"

using namespace std;

int main(int argc, char *argv[])
{

	Log::Instance()->Info("main::main", "Starting app");

#if defined(__APPLE__) && defined(__MACH__)
	string resource_folder = string(filesystem::path(string(argv[0])).remove_filename()) + "/" + "resources";
#else
	string resource_folder = "resources";
#endif

	if (argc > 1)
	{
		resource_folder = argv[1];
	}
	GemEngine app = GemEngine(resource_folder);

	SceneManager::Instance()->AddSceneLogic("Start Scene", new Scene1());
	SceneManager::Instance()->AddSceneLogic("Second Scene", new Scene2());
	SceneManager::Instance()->AddSceneLogic("Third Scene", new Scene3());

	int status = -1;
	try
	{
		status = app.Start();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	Log::Instance()->Info("main::main", "Exiting app");

	return status;
}
