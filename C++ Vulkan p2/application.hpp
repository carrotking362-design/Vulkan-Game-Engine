#pragma once

#include "lve_window.hpp"

namespace lve {
class application {
private:
    LveWindow LveWindow{WIDTH, HEIGHT, "Vulkan Application"};

public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    void run();
};
}