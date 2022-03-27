#pragma once
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <assert.h>
#include <string>
#include <memory>

namespace Galaxy {

    class Window
    {
    private:
        GLFWwindow* glfw_handle;
        int width, height;
        bool focus;
        bool maximized;
        bool minimized;
    public:
        Window(const std::string& title, const int width, const int height, bool resizable = true, int samples = 4);

        /* Functions */
        GLFWwindow* GetWindow() const { return glfw_handle; }
        void operator=(const Window&) = delete;
        Window() = delete;


        void SetIcon(const std::string& filepath) const;
        bool ShouldClose()                          const { return glfwWindowShouldClose(glfw_handle); }
        void MakeContextCurrent()                   const { glfwMakeContextCurrent(glfw_handle); }
        void SwapBuffers()                          const { glfwSwapBuffers(glfw_handle); }
        void PollEvents()                           const { glfwPollEvents(); }
        void SetTitle(const std::string& newTitle)  const { glfwSetWindowTitle(glfw_handle, newTitle.c_str()); }
        void SetVSyncEnabled(bool enabled)          const { glfwSwapInterval(enabled); }
        const int GetWidth()                        const { return width; }
        const int GetHeight()                       const { return height; }
        const float GetAspectRatio()                const { return (float)width / (float)height; }


        //Callbacks
        static void Close();
        static void OnError(int error, const char* message);
        static void OnFramebufferResize(GLFWwindow* window, int width, int height);
        static void OnWindowResize(GLFWwindow* window, int width, int height);
        static void OnMaximize(GLFWwindow* window, int maximized);
        static void OnFocus(GLFWwindow* window, int focused);
        static void OnMove(GLFWwindow* window, int x, int y);
        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void MouseCallback(GLFWwindow* window, int button, int action, int mods);
    };
}
