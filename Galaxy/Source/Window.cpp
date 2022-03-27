#include "Window.h"
#include "Log.h"
#include "InputManager.h"
#include <stb/stb_image.h>
#include "Dialog.h"

namespace Galaxy {
    Window::Window(const std::string& title, const int width, const int height, bool resizable, int samples)
        : glfw_handle(nullptr), width(width), height(height), focus(false), maximized(false), minimized(false)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, resizable);
        glfwWindowHint(GLFW_SAMPLES, samples);
        glfw_handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!glfw_handle) {
            LOG_ERROR("Failed to create a GLFW window!");
            if(Dialog::MessageBox("Error.", "Failed to create a GLFW window!", MessageBoxType::OK, MessageBoxVerbose::ERROR))
                _exit(EXIT_FAILURE);
        }
        glfwSetErrorCallback(OnError);
        glfwSetFramebufferSizeCallback(glfw_handle, OnFramebufferResize);
        glfwSetWindowSizeCallback(glfw_handle, OnWindowResize);
        glfwSetWindowFocusCallback(glfw_handle, OnFocus);
        glfwSetWindowMaximizeCallback(glfw_handle, OnMaximize);
        glfwSetKeyCallback(glfw_handle, InputManager::KeyCallback);
        glfwSetMouseButtonCallback(glfw_handle, InputManager::MouseCallback);

        this->MakeContextCurrent();
        SetVSyncEnabled(true);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            LOG_ERROR("Couldn't initialize GLAD.");
            _exit(EXIT_FAILURE);
        }

        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
    }


    void Window::SetIcon(const std::string& filepath) const
    {
        GLFWimage icon;
        int ch;
        icon.pixels = stbi_load(filepath.c_str(), &icon.width, &icon.height, &ch, 0);
        glfwSetWindowIcon(glfw_handle, 1, &icon);
        stbi_image_free(icon.pixels);
    }

    void Window::Close()
    {
        
    }

    void Window::OnError(int error, const char* message)
    {
        LOG_ERROR("[GLFW] Error code {}: {}", error, message);
        _exit(EXIT_FAILURE);
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
        if(maximized == GLFW_TRUE)
            LOG_TRACE("[WINDOW] Window maximized");
        else if(maximized == GLFW_FALSE)
            LOG_TRACE("[WINDOW] Window restored");

    }
    void Window::OnFocus(GLFWwindow* window, int focused)
    {
        if (focused) LOG_TRACE("[WINDOW] Focusing window.");
        else LOG_TRACE("[WINDOW] Losing focus on window.");
    }

    void Window::OnMove(GLFWwindow* window, int x, int y)
    {
        LOG_TRACE("[WINDOW] Moving window: ({}, {})", x, y);
    }

    void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
    }

    void Window::MouseCallback(GLFWwindow* window, int button, int action, int mods)
    {
    }
}

