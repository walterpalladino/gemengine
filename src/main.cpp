#include <iostream>
#include "App.h"
#include "utils/Log.h"
#include "utils/StringUtils.h"
#include "core/Config.h"
#include <fstream> // File io header

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

	Log::Instance()->Info("main::main", "Exiting app");

	return status;
}
