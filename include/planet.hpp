#ifndef PLANET_HPP
#define PLANET_HPP

#include <glm/glm.hpp>

struct Planet {
    glm::vec3 position;
    glm::vec3 velocity;
    float mass;
    float radius; // Derived from diameter
};

#endif // PLANET_HPP