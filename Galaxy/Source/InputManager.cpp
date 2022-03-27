#include "InputManager.h"

namespace Galaxy
{
	InputManager& InputManager::Get()
	{
		static InputManager instance = InputManager();
		return instance;
	}

	void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
			Get().keyPressed[key] = true;

		else if (action == GLFW_RELEASE)
			Get().keyPressed[key] = false;
	}

	void InputManager::MouseCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS)
			Get().mouseBtnPressed[button] = true;

		else if (action == GLFW_RELEASE)
			Get().mouseBtnPressed[button] = false;
	}

	bool InputManager::GetKeyPressed(const KeyCode& key)
	{
		if ((int)key != -1)
			return Get().keyPressed[(int)key];
		else return false;
	}

	bool InputManager::GetMouseButtonPressed(const MouseButton& button)
	{
		if ((int)button != -1)
			return Get().mouseBtnPressed[(int)button];
		else return false;
	}
}

