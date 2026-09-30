#include "lve_pipeline.hpp"

#include <fstream>
#include <stdexcept>
#include <vector>

namespace lve {
    std::vector<char> LvePipeline::readFile(const std::string& filePath) {
        std::ifstream file{filePath, std::ios::ate | std::ios::binary};
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();
        return buffer;
    }
}