# Vulkan Physics Simulation

## Overview
The Vulkan Physics Simulation project is designed to create a framework for simulating planetary physics using Vulkan for rendering. The initial setup focuses on creating an empty window where future simulations will take place.

## Project Structure
```
vulkan-physics-sim
├── include
│   └── vulkan_app.hpp
├── src
│   ├── main.cpp
│   └── vulkan_app.cpp
├── shaders
│   ├── shader.frag
│   └── shader.vert
├── CMakeLists.txt
└── README.md
```

## Requirements
- C++17 or later
- Vulkan SDK
- GLFW library

## Setup Instructions
1. **Install Vulkan SDK**: Follow the instructions on the official Vulkan website to install the Vulkan SDK for your platform.
2. **Install GLFW**: You can install GLFW via package managers or build it from source.
3. **Clone the repository**: 
   ```
   git clone <repository-url>
   cd vulkan-physics-sim
   ```
4. **Build the project**:
   - Create a build directory:
     ```
     mkdir build
     cd build
     ```
   - Run CMake:
     ```
     cmake ..
     ```
   - Compile the project:
     ```
     cmake --build .
     ```

## Running the Application
After building the project, you can run the application from the build directory. The application will open an empty window, which will serve as the canvas for future planetary simulations.

## Future Work
- Implement the rendering of planets and physics simulations.
- Develop shaders for rendering.
- Enhance user interaction and controls for simulation parameters.