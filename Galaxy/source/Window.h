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
    public:
        Window(std::string title, int width, int const height, bool resizable = true, int samples = 4);

        /* Functions */
        GLFWwindow* GetWindow() const { assert(window != nullptr); return window; }
        Window(Window& other) = delete;
        void operator=(const Window&) = delete;
        Window() = delete;


        bool Check();
        bool ShouldClose()                  const { return glfwWindowShouldClose(window); }
        void MakeContextCurrent()           const { glfwMakeContextCurrent(window); }
        void SwapBuffers()                  const { glfwSwapBuffers(window); }
        void SetTitle(std::string newTitle) const { glfwSetWindowTitle(window, newTitle.c_str()); }
        void SetVSyncEnabled(bool enabled)  const { glfwSwapInterval(enabled); }
        int GetWidth()                      const { return width; }
        int GetHeight()                     const { return height; }


    };
}
