#include <iostream>
#include "App.h"
#include "utils/Log.h"
#include "utils/StringUtils.h"

using namespace std;

int main(int argc, char *argv[])
{

	Log::GetInstance()->Info("main::main", "Starting app");

	App app = App();

	if (argc > 1)
	{
		app.SetResourceFolder(argv[1]);
	}
	else
	{
		app.SetResourceFolder("Resources");
	}

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
