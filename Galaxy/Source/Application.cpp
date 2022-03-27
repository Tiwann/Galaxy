#include "Application.h"
#include "Dialog.h"

namespace Galaxy
{
	Application::Application()
		: mainWindow(nullptr), windows(std::vector<Window*>())
	{
		Log::Init();
		if(!glfwInit())
		{
			if(Dialog::MessageBox("Error", "Failed to initialize GLFW!", MessageBoxType::OK, MessageBoxVerbose::ERROR))
				_exit(EXIT_FAILURE);
		}
		
		mainWindow = new Window("Galaxy Renderer", 1280, 720, false, 16);

		if(!mainWindow)
		{
			if(Dialog::MessageBox("Error", "Failed to create window!", MessageBoxType::OK, MessageBoxVerbose::ERROR))
				_exit(EXIT_FAILURE);
		}
		mainWindow->SetIcon("Assets/icon48x48.png");
		windows.push_back(mainWindow);

	}

	void Application::CreateWindow(Window* newWindow)
	{
		windows.push_back(newWindow);
	}

	void Application::Run()
	{
		LOG_TRACE("Welcome to Galaxy Renderer version {}.{}!", GALAXY_VERSION_MAJOR, GALAXY_VERSION_MINOR);
	}

	void Application::Close()
	{

	}
}

