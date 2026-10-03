#include "lve_pipeline.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

namespace lve {

LvePipeline::LvePipeline(
    LveDevice& device, const std::string& vertFilePath, const std::string& fragFilePath)
    : lveDevice{device} {
    createGraphicsPipeline(vertFilePath, fragFilePath);
}

// Read raw SPIRV byte streams from disk:
std::vector<char> LvePipeline::readFile(const std::string& filePath) {
    // Open the file at the end (std::ios::ate)
    // Read the file in binary (std::ios::binary):
    std::ifstream file{filePath, std::ios::ate | std::ios::binary};

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    // Returns the file size instantly cus you started at the end:
    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize); // Reserve vector in memory.

    // Seek back to the start of the file and read the content into the buffer:
    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    return buffer;
}

void LvePipeline::createGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath) {
    // Load verity and fragment bytecode into Ram:
    auto vertCode = readFile(vertFilePath);
    auto fragCode = readFile(fragFilePath);

    std::cout << "Vertex Shader Code Size: " << vertCode.size() << std::endl;
    std::cout << "Fragment Shader Code Size: " << fragCode.size() << std::endl;
}
}
