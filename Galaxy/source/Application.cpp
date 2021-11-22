#include <GLFW/glfw3.h>
#include "Log/Log.h"


int main() {
    Log::Init();
    
    if (!glfwInit()) {
        LOG_INFO("Couldn't initalize GLFW.");
        return -1;
    }

    LOG_INFO("Using GLFW version {}.{}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR)


    return 0;
}