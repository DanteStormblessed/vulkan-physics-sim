#include <vulkan_app.hpp>
#include <filesystem>
#include <iostream>

int main() {
    std::cout << "Actual Directory: " << std::filesystem::current_path() << std::endl;

    VulkanApp app;

    app.initialize();
    app.run();
    app.cleanup();

    return 0;
}