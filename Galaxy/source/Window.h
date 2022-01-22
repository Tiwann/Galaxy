#pragma once
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <assert.h>
#include <string>
#include <memory>

namespace Galaxy {

    class Window
    {
    private:
        GLFWwindow* window;
        inline static Window* instance = nullptr;
        int width, height;
        bool focus;
        bool miximized;
    public:
        Window(std::string title, const int width, const int height, bool resizable = true, int samples = 4);

        /* Functions */
        GLFWwindow* GetWindow() const { assert(window != nullptr); return window; }
        Window(Window& other) = delete;
        void operator=(const Window&) = delete;
        Window() = delete;


        bool Check();
        bool ShouldClose()                  const { return glfwWindowShouldClose(window); }
        void MakeContextCurrent()           const { glfwMakeContextCurrent(window); }
        void SwapBuffers()                  const { glfwSwapBuffers(window); }
        void PollEvents()                   const { glfwPollEvents(); }
        void SetTitle(std::string newTitle) const { glfwSetWindowTitle(window, newTitle.c_str()); }
        void SetVSyncEnabled(bool enabled)  const { glfwSwapInterval(enabled); }
        const int GetWidth()                const { return width; }
        const int GetHeight()               const { return height; }
        const float GetAspectRatio()        const { return (float)width / (float)height; }


        //Callbacks
        static void OnFramebufferResize(GLFWwindow* window, int width, int height);
        static void OnWindowResize(GLFWwindow* window, int width, int height);
        static void OnMaximize(GLFWwindow* window, int maximized);
        static void OnFocus(GLFWwindow* window, int focused);
        static void OnMove(GLFWwindow* window, int xpos, int ypos);
        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void MouseCallback(GLFWwindow* window, int button, int action, int mods);
    };
}
