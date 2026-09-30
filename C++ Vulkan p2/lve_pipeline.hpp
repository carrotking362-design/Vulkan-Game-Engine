#pragma once

#include <string>
#include <vector>

namespace lve {
class LvePipeline {
private:
    static std::vector<char> readFile(const std::string& filePath);
    void createGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath) {}
public:
    LvePipeline(const std::string& vertFilePath, const std::string& fragFilePath);
};
}