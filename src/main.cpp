#include <iostream>
#include "App.h"
#include "utils/Log.h"

using namespace std;

int main(int argc, char *argv[])
{

	Log::GetInstance()->Info("main::main", "Starting app");

	/*
		// print all command line arguments
		cout << "name of program: " << argv[0] << '\n';

		if (argc > 1)
		{
			cout << "there are " << argc - 1 << " (more) arguments, they are:\n";

			copy(argv + 1, argv + argc, ostream_iterator<const char *>(cout, "\n"));
		}

		for (int i = 0; i < argc; ++i)
			cout << argv[i] << '\n';

			const char *filename = argc > 1 ? argv[1] : "test.png";

	SceneLoader::GetInstance()->Load("./resources/scenes/scene_1.txt");
	*/

	App app = App();

	if (argc > 1)
	{
		app.SetResourceFolder(argv[1]);
	}
	else
	{
		app.SetResourceFolder("Resources");
	}

	cout << "Resources folder: " << app.GetResourceFolder() << endl;

	// app.LoadScenes();

	int status = -1;
	try
	{
		//		status = app.Execute(argc, argv);
		status = app.Start(1280, 720, 384, 216);
		// status = app.Start(1280, 720);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	app.Cleanup();

	Log::GetInstance()->Info("main::main", "Exiting app");

	return status;
}
