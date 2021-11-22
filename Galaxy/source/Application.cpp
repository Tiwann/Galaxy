#include "GLFW/glfw3.h"
#include <iostream>

int main() {
    if (!glfwInit()) {
        std::cout << "Couldn't initalize GLFW." << std::endl;
        return -1;
    }


    return 0;
}