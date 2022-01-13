#include "Window.h"
#include "Log.h"
#include <stb/stb_image.h>

namespace Galaxy {
    Window::Window(std::string title, int width, int const height, bool resizable, int samples)
        : window(nullptr), width(width), height(height)
    {
        if (instance != nullptr)
        {
            LOG_ERROR("Cannot have two instances of Window class! Crashing.");
        }

        if (!glfwInit()) {
            Galaxy::LOG_ERROR("Couldn't initalize GLFW.");
            __debugbreak();
        }

        assert(instance == nullptr);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, resizable);
        glfwWindowHint(GLFW_SAMPLES, samples);
        this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        GLFWimage icon;
        int ch;
        icon.pixels = stbi_load("Assets/icon48x48.png", &icon.width, &icon.height, &ch, 0);
        glfwSetWindowIcon(window, 1, &icon);
    }

    bool Window::Check()
    {
        if (!window) {
            Galaxy::LOG_ERROR("Failed to create a window.");
            return false;
        }

        MakeContextCurrent();
        SetVSyncEnabled(true);

        if (glewInit() != GLEW_OK) {
            Galaxy::LOG_ERROR("Couldn't initalize GLEW.");
            return false;
        }

        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
    }
}

