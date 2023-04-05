#include <iostream>
#include "Game.h"

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

	Game game = Game();

	int status = -1;
	try
	{
		status = game.Execute(argc, argv);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	return status;
}
