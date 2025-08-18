#ifndef VULKAN_APP_HPP
#define VULKAN_APP_HPP

// Fuerza convención de Vulkan y radianes antes de incluir glm
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include "sphere_model.hpp"

class VulkanApp {
public:
    VulkanApp();
    void initialize();
    void run();
    void cleanup();

private:
    // Add new members for the sphere model
    SphereModel sphereModel;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;
    VkBuffer uniformBuffer;
    VkDeviceMemory uniformBufferMemory;

    // New methods for handling 3D objects
    void createVertexBuffer();
    void createIndexBuffer();
    void createUniformBuffers();
    void createDescriptorSetLayout();
    void createDescriptorPool();
    void createDescriptorSets();
    void updateUniformBuffer();

    // Camera state and input
    void processInput(float deltaTime);
    void onMouseMove(double xpos, double ypos);
    bool firstMouse = true;
    float lastX = 0.0f, lastY = 0.0f;
    glm::vec3 cameraPos{0.0f, 0.0f, 3.0f};
    glm::vec3 cameraFront{0.0f, 0.0f, -1.0f};
    glm::vec3 cameraUp{0.0f, 1.0f, 0.0f};
    float yaw = -90.0f;   // mirando hacia -Z
    float pitch = 0.0f;
    float fov = 45.0f;
    float moveSpeed = 3.0f;       // unidades/seg
    float mouseSensitivity = 0.1f;

    // Structure for uniform data (transformation matrices)
    struct UniformBufferObject {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    };

    // Auxiliary functions
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                     VkMemoryPropertyFlags properties, VkBuffer& buffer,
                     VkDeviceMemory& bufferMemory);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    // Existing methods...
    void createWindow();
    void createInstance();
    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSwapChain();
    void createImageViews();
    void createRenderPass();
    void createGraphicsPipeline();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffers();
    void createSyncObjects();
    void drawFrame();
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    // Existing members
    GLFWwindow* window;
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkSurfaceKHR surface;
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;
    VkSemaphore imageAvailableSemaphore;
    VkSemaphore renderFinishedSemaphore;
    VkFence inFlightFence;
};

#endif // VULKAN_APP_HPP