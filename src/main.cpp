#include <iostream>
#include "App.h"

using namespace std;

int main(int argc, char *argv[])
{
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
	*/

	App app = App();

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

	return status;
}
