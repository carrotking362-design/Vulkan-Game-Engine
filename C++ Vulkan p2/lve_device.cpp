// Forces Glm angles to be radians, not degrees.
#define GLM_FORCE_RADIANS 
// Forces Glms projection matrices to match Vulkans clip depth range of [0.0, 1.0], instead of Opengls [-1.0, 1.0]:
#define GLM_FORCE_DEPTH_ZERO_TO_ONE 
#include <glm/glm.hpp>

#include "lve_device.hpp"

#include <iostream>
#include <stdexcept>
#include <unordered_set>

namespace lve {

LveDevice::LveDevice(LveWindow& window) : window{window} {
    initVulkan();
}

LveDevice::~LveDevice() {
    // Destroys the Vulkan instance if the handle is not valid:
    if (instance != VK_NULL_HANDLE) {
        vkDestroyInstance(instance, nullptr);
    }
}

void LveDevice::initVulkan() {
    createInstance();
}

void LveDevice::createInstance() {
    // Structure which provides detail about the application:
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan Engine";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // Tells Vulkan which extensions and layers to enable:
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // Gets required Glfw extensions and confirms your drivers support:
    auto extensions = getRequiredExtensions();
    checkRequiredExtensions();

    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();
    createInfo.enabledLayerCount = 0;
    createInfo.pNext = nullptr;

    printAvailableExtensions();

    // Throws exception if Vulkan instance failed to create:
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create instance.");
    }
}

std::vector<const char*> LveDevice::getRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    // Const char double pointer represents an array of str (Ts for Jarvis).
    // Get required Glfw platform window surface extension names:
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    // Preprocessor checks if the macro __APPLE__ exists (It will If youre on mac).
    // If it does, It keeps the line of code:
#ifdef __APPLE__
    // Tells Vulkan to allow Apples MoltenVK translation layer:
    extensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif
    return extensions;
}

void LveDevice::checkRequiredExtensions() {
    std::vector<const char*> requiredExtensions = getRequiredExtensions();

    // Get total number of instance extensions available on the system driver:
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr); // Updates extension count.

    // Populate the vector with supported extensions: 
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

    // Insert extension names into a hash set:
    std::unordered_set<std::string> availableNames;
    for (const auto& extension : availableExtensions) {
        availableNames.insert(extension.extensionName);
    }

    // Verify all required extensions are available in the set:
    std::cout << "Required instance extensions:\n";
    for (const auto& required : requiredExtensions) {
        std::cout << "\t" << required;
        // If the extension is not found throw an error:
        if (availableNames.find(required) == availableNames.end()) {
            std::cout << " [MISSING]\n";
            throw std::runtime_error(std::string("Missing required extension: ") + required);
        }
        std::cout << "\n";
    }
}

void LveDevice::printAvailableExtensions() {
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    std::cout << "\nAvailable extensions (" << extensionCount << "):\n";
    for (const auto& extension : extensions) {
        std::cout << "\t" << extension.extensionName << '\n';
    }
    std::cout << '\n';
}
}