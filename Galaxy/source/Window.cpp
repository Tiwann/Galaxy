#include "Window.h"
#include "Log.h"
#include "Input.h"
#include <stb/stb_image.h>

namespace Galaxy {
    Window::Window(std::string title, const int width, const int height, bool resizable, int samples)
        : window(nullptr), width(width), height(height), focus(false), miximized(false)
    {
        if (instance != nullptr)
        {
            LOG_ERROR("Cannot have two instances of Window class! Crashing.");
        }

        if (!glfwInit()) {
            LOG_ERROR("Couldn't initalize GLFW.");
            __debugbreak();
        }

        assert(instance == nullptr);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, resizable);
        glfwWindowHint(GLFW_SAMPLES, samples);
        this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        GLFWimage icon;
        int ch;
        icon.pixels = stbi_load("Assets/icon48x48.png", &icon.width, &icon.height, &ch, 0);
        glfwSetWindowIcon(window, 1, &icon);
        glfwSetFramebufferSizeCallback(window, Window::OnFramebufferResize);
        glfwSetWindowSizeCallback(window, Window::OnWindowResize);
        glfwSetWindowFocusCallback(window, Window::OnFocus);
        glfwSetWindowMaximizeCallback(window, Window::OnMaximize);
        glfwSetKeyCallback(window, Window::KeyCallback);
        glfwSetMouseButtonCallback(window, Window::MouseCallback);
    }

    
    bool Window::Check()
    {
        if (!window) {
            LOG_ERROR("Failed to create a window.");
            return false;
        }

        MakeContextCurrent();
        SetVSyncEnabled(true);

        if (glewInit() != GLEW_OK) {
            LOG_ERROR("Couldn't initalize GLEW.");
            return false;
        }

        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
        
        return true;
    }

    void Window::OnFramebufferResize(GLFWwindow* window, int width, int height)
    {
        LOG_TRACE("[OPENGL] Framebuffer resized: ({}, {})", width, height);
        glViewport(0, 0, width, height);
    }

    void Window::OnWindowResize(GLFWwindow* window, int width, int height)
    {
        
    }

    void Window::OnMaximize(GLFWwindow* window, int maximized)
    {
        if (maximized)
            LOG_TRACE("[WINDOW] Window maximized");

    }
    void Window::OnFocus(GLFWwindow* window, int focused)
    {
        if (focused) LOG_TRACE("[WINDOW] Focusing window.");
        else LOG_TRACE("[WINDOW] Losing focus on window.");
    }

    void Window::OnMove(GLFWwindow* window, int xpos, int ypos)
    {
        LOG_TRACE("[WINDOW] Moving window: ({}, {})", xpos, ypos);
    }

    void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        LOG_TRACE("[WINDOW] Key Callback: {}, {}, {}, {}", key, scancode, action, mods);
        
    }

    void Window::MouseCallback(GLFWwindow* window, int button, int action, int mods)
    {
        LOG_TRACE("[WINDOW] Mouse Button Callback: {}, {}, {}", button, action, mods);
    }
}

