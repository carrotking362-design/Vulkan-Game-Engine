#pragma once

#define GLFW_INCLUDE_VULKAN // Forces glfw to use a vulkan context instead of OpenGl
#include <GLFW/glfw3.h>
#include <iostream>

namespace lve {
class LveWindow {
private:
    GLFWwindow* window;

    void initWindow();

    const uint32_t WIDTH;
    const uint32_t HEIGHT;
    std::string windowName;

public:
    LveWindow(const uint32_t w, const uint32_t h, std::string name);
    ~LveWindow();
    
    // Disable the copy constructor op and the copy assignment op:
    LveWindow(const LveWindow& other) = delete;
    LveWindow &operator=(const LveWindow& other) = delete;

    bool shouldClose() { return glfwWindowShouldClose(window); } // Helper func
};
}