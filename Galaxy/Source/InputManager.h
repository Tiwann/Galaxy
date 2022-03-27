#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include "KeyCode.h"
#include "Log.h"

namespace Galaxy
{
	class InputManager
	{
	private:
		InputManager(){}
		std::vector<bool> keyPressed = std::vector<bool>((int)KeyCode::TOTAL);
		std::vector<bool> mouseBtnPressed = std::vector<bool>((int)MouseButton::TOTAL);
	public:
		static InputManager& Get();
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseCallback(GLFWwindow* window, int button, int action, int mods);

		static bool GetKeyPressed(const KeyCode& key);
		static bool GetMouseButtonPressed(const MouseButton& button);
	};
}


