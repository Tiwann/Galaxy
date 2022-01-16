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

    };
}
