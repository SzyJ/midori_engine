#pragma once

#include "Core.h"

namespace Midori {

	class MIDORI_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

    // To be defined in client
    Application* CreateApplication();
}
