cmake_minimum_required(VERSION 3.10)

project(VulkanPhysicsSim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# Directory for compiled shaders
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/shaders)

# Find all shaders
file(GLOB_RECURSE GLSL_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/shaders/*.frag"
    "${PROJECT_SOURCE_DIR}/shaders/*.vert"
    "${PROJECT_SOURCE_DIR}/shaders/*.comp"
    "${PROJECT_SOURCE_DIR}/shaders/*.geom"
    "${PROJECT_SOURCE_DIR}/shaders/*.tesc"
    "${PROJECT_SOURCE_DIR}/shaders/*.tese"
)

# Function to compile each shader
foreach(GLSL ${GLSL_SOURCE_FILES})
    get_filename_component(FILE_NAME ${GLSL} NAME)
    set(SPIRV "${CMAKE_BINARY_DIR}/shaders/${FILE_NAME}.spv")
    add_custom_command(
        OUTPUT ${SPIRV}
        COMMAND ${Vulkan_GLSLANG_VALIDATOR_EXECUTABLE} -V ${GLSL} -o ${SPIRV}
        DEPENDS ${GLSL}
        COMMENT "Compiling shader ${FILE_NAME}"
    )
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

# Custom target to compile all shaders
add_custom_target(
    shaders 
    DEPENDS ${SPIRV_BINARY_FILES}
)

file(GLOB SOURCES
    src/*.cpp
)

# Explicitly add sphere_model.cpp if it's in a different location
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/sphere_model.cpp)

# Create the executable target first
add_executable(${PROJECT_NAME} ${SOURCES})

# Now, specify the include directories for that target.
target_include_directories(${PROJECT_NAME} PUBLIC 
    "${PROJECT_SOURCE_DIR}/include"
    ${GLM_INCLUDE_DIRS}
)

# Link the libraries to the target
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan glfw)

# Make the executable build depend on the shaders
add_dependencies(${PROJECT_NAME} shaders)

# Copy the shaders to the build directory (optional, if you prefer to keep them separate)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_BINARY_DIR}/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
)