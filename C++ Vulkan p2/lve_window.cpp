#include "lve_window.hpp"

namespace lve {
LveWindow::LveWindow(const uint32_t w, const uint32_t h, std::string name)
    : WIDTH{w}, HEIGHT{h}, windowName{name} {
    initWindow();
}

LveWindow::~LveWindow() {
    // Disables callbacks.
    // If the rendering context is still active it is detached from the main thread:
    glfwDestroyWindow(window); 
    // Unloads the Glfw library:
    glfwTerminate();
}

void LveWindow::initWindow() {
    glfwInit(); // Initialises Glfw library.
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Tells Glfw to not use an Opengl context.
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Cant resize window

    window = glfwCreateWindow(WIDTH, HEIGHT, windowName.c_str(), nullptr, nullptr);
}
}
