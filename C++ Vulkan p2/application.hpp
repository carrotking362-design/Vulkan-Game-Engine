#pragma once

#include "lve_window.hpp"
#include "lve_device.hpp"
#include "lve_pipeline.hpp"

namespace lve {
class application {
public:
    // Window dimentions:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    void run();

private:
    // MUST initialise in this order because each one is dependent on the one before it:
    LveWindow lveWindow{WIDTH, HEIGHT, "Vulkan Application"};
    LveDevice lveDevice{lveWindow};
    LvePipeline lvePipeline{lveDevice, "Shaders/vert.spv", "Shaders/frag.spv"};
};
}
