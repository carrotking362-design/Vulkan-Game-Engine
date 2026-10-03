#pragma once

#define GLFW_INCLUDE_VULKAN // Forces glfw to use a Vulkan context.
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "lve_window.hpp"

#include <vector>
#include <string>

namespace lve {
class LveDevice {
private:
    void initVulkan();
    void createInstance();

    std::vector<const char*> getRequiredExtensions();
    void checkRequiredExtensions();
    void printAvailableExtensions();

    LveWindow& window;
    VkInstance instance{VK_NULL_HANDLE};
public:
    explicit LveDevice(LveWindow& window);
    ~LveDevice();

    // RAII Protection:
    LveDevice(const LveDevice& other) = delete;
    LveDevice& operator = (const LveDevice& other) = delete;
    LveDevice(const LveDevice&& other) = delete;
    LveDevice& operator = (const LveDevice&&) = delete;

    VkInstance getInstance() const { return instance; }
};
}