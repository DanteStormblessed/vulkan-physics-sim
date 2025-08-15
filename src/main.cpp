#include <vulkan_app.hpp>

int main() {
    VulkanApp app;

    app.initialize();
    app.run();
    app.cleanup();

    return 0;
}