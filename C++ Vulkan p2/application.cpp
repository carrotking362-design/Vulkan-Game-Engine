#include "application.hpp"

namespace lve {
    void application::run() {
        while (!LveWindow.shouldClose()) {
            glfwPollEvents();
        }
    }
}