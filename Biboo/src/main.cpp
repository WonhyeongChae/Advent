#include "Application.h"

auto main() -> int
{
	using namespace Engine;

	Application engineApp;

	if (engineApp.Initialize())
	{
		while (engineApp.IsRunning())
		{
			engineApp.Update();
		}
	}

	return EXIT_SUCCESS;
}