﻿#include "Window.h"
#include "Log/Log.h"

namespace Galaxy {
    Window::Window(std::string title, int width, int const height, bool resizable, int samples)
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

        glfwWindowHint(GLFW_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_RESIZABLE, resizable);
        glfwWindowHint(GLFW_SAMPLES, samples);
        this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    }

    Window* Window::Create(std::string title, int width, int const height, bool resizable, int samples)
    {
        instance = new Window(title, width, height, resizable, samples);
        return instance;
    }
}

