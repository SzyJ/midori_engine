#include "Application.h"

#include <stdio.h>

namespace Midori {
	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run() {
        printf("Hello World from Midori!\n");
		while (true);
	}
}
