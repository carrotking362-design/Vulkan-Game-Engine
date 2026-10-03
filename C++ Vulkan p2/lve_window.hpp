#pragma once

// Tells Glfw to use a Vulkan Context:
#define GLFW_INCLUDE_VULKAN 
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
    
    // RAII Protection:
    LveWindow(const LveWindow& other) = delete;
    LveWindow &operator=(const LveWindow& other) = delete;

    bool shouldClose() { return glfwWindowShouldClose(window); }
};
}
