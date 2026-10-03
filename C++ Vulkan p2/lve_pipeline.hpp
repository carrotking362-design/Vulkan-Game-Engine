#pragma once

#include "lve_device.hpp"

#include <string>
#include <vector>

namespace lve {
class LvePipeline {
public:
    LvePipeline(
        LveDevice& device, 
        const std::string& vertFilePath, 
        const std::string& fragFilePath);

    ~LvePipeline() = default;

    // RAII protection:
    LvePipeline(const LvePipeline&) = delete;
    LvePipeline& operator=(const LvePipeline&) = delete;

private:
    static std::vector<char> readFile(const std::string& filePath);
    void createGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath);

    LveDevice& lveDevice;
};
}
