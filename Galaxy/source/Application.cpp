#include <GL/glew.h>
#include <glfw/glfw3.h>
#include "Log/Log.h"
#include "Window/Window.h"


#define GALAXY_VERSION_MAJOR 0
#define GALAXY_VERSION_MINOR 1

int main() {
    Log::Init();
    
    LOG_TRACE("Welcome to Galaxy Renderer version {}.{}!", GALAXY_VERSION_MAJOR, GALAXY_VERSION_MINOR)

    if (!glfwInit()) {
        LOG_ERROR("Couldn't initalize GLFW.")
        return -1;
    }


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window* window = Window::Create("Galaxy", 600, 600, false, 16);

    if (!window->GetWindow()) {
        LOG_ERROR("Failed to create a window.")
        return -1;
    }

    window->MakeContextCurrent();

    if (glewInit() != GLEW_OK) {
        LOG_ERROR("Couldn't initalize GLEW.");
        return -1;
    }

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_FRAMEBUFFER_SRGB);

    LOG_TRACE("Using GLFW version {}.{}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR)
    LOG_TRACE("Using GLEW version {}.{}.{}", GLEW_VERSION_MAJOR, GLEW_VERSION_MINOR, GLEW_VERSION_MICRO)
    LOG_TRACE("Using OpenGL: {}", glGetString(GL_VERSION))

    while (!window->ShouldClose()) 
    {
        glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap back and front buffers
        window->SwapBuffers();
        glfwPollEvents();
    }
    


    return 0;
}