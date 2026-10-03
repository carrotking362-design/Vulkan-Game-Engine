#include "application.hpp"

namespace lve {

void application::run() {
    // Keeps processing window events + rendering until user closes window:
    while (!lveWindow.shouldClose()) {
        // Processes os input events:
        glfwPollEvents();
    }
}
}
