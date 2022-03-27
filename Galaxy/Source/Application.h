#pragma once
#include "Log.h"
#include "Window.h"

#define GALAXY_VERSION_MAJOR 0
#define GALAXY_VERSION_MINOR 3

namespace Galaxy
{
	class Application
	{
	private:
		Window* mainWindow;
		std::vector<Window*> windows;
	public:
		Application();
		~Application() = default;

		static Application& Get()
		{
			static Application instance = Application();
			return instance;
		}

		const std::vector<Window*>& GetWindows() const { return windows; }
		const Window* GetMainWindow() const { return mainWindow; }
		void CreateWindow(Window* newWindow);
		void Run();
		void Close();
	};
}
