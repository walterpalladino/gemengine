#include <iostream>
#include "App.h"
#include "utils/Log.h"
#include "utils/StringUtils.h"
#include "core/Config.h"

using namespace std;

int main(int argc, char *argv[])
{

	Log::GetInstance()->Info("main::main", "Starting app");

	string resource_folder = "Resources";
	if (argc > 1)
	{
		resource_folder = argv[1];
	}
	App app = App(resource_folder);

	int status = -1;
	try
	{
		status = app.Start();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	app.Cleanup();

	Log::GetInstance()->Info("main::main", "Exiting app");

	return status;
}
