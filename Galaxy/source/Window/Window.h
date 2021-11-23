#pragma once
#include "GLFW/glfw3.h"
#include <assert.h>
#include <string>

namespace Galaxy {

    class Window
    {
    private:
        GLFWwindow* window;
        inline static Window* instance = nullptr;
        Window(std::string title, int width, int const height, bool resizable = true, int samples = 4);
    public:

        /* Constructor */
        static Window* Create(std::string title, int width, int const height, bool resizable, int samples);

        /* Functions */
        GLFWwindow* GetWindow() const { assert(window != nullptr); return window; }
        Window(Window& other) = delete;
        void operator=(const Window&) = delete;

        bool ShouldClose()                  const { return glfwWindowShouldClose(window); }
        void MakeContextCurrent()           const { glfwMakeContextCurrent(window); }
        void SwapBuffers()                  const { glfwSwapBuffers(window); }
        void SetTitle(std::string newTitle) const { glfwSetWindowTitle(window, newTitle.c_str()); }
        void SetVSyncEnabled(bool enabled)  const { glfwSwapInterval(enabled); }
    };
}
