cmake_minimum_required(VERSION 3.10)

project(VulkanPhysicsSim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

file(GLOB SOURCES
    src/*.cpp
)

# Create the executable target first
add_executable(${PROJECT_NAME} ${SOURCES})

# Now, specify the include directories for that target.
# It's good practice to use target_include_directories for all includes.
target_include_directories(${PROJECT_NAME} PUBLIC 
    "${PROJECT_SOURCE_DIR}/include"
    ${GLM_INCLUDE_DIRS}
)

# Link the libraries to the target
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan glfw)