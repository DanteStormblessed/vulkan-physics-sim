#include "sphere_model.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <cmath>

SphereModel::SphereModel(float radius, int sectors, int stacks) {
    generateVertices(radius, sectors, stacks);
    generateIndices(sectors, stacks);
}

void SphereModel::generateVertices(float radius, int sectors, int stacks) {
    float sectorStep = 2 * M_PI / sectors;
    float stackStep = M_PI / stacks;
    
    vertices.clear();
    
    for (int i = 0; i <= stacks; ++i) {
        float stackAngle = M_PI / 2 - i * stackStep;  // starting from pi/2 to -pi/2
        float xy = radius * cosf(stackAngle);
        float z = radius * sinf(stackAngle);
        
        // add (sectors+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= sectors; ++j) {
            float sectorAngle = j * sectorStep;  // starting from 0 to 2pi
            
            // vertex position
            float x = xy * cosf(sectorAngle);
            float y = xy * sinf(sectorAngle);
            
            // vertex normal
            glm::vec3 normal = glm::normalize(glm::vec3(x, y, z));
            
            // add vertex data
            vertices.push_back({{x, y, z}, {normal.x, normal.y, normal.z}, {1.0f, 1.0f, 1.0f}});
        }
    }
}

void SphereModel::generateIndices(int sectors, int stacks) {
    indices.clear();
    
    for (int i = 0; i < stacks; ++i) {
        int k1 = i * (sectors + 1);
        int k2 = k1 + sectors + 1;
        
        for (int j = 0; j < sectors; ++j, ++k1, ++k2) {
            // 2 triangles per sector excluding the first and last stacks
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            
            if (i != (stacks - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}