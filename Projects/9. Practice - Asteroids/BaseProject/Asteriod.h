#pragma once
#include <camera/camera.h>

#include "Settings.h"
#include "GameObject.h"

enum Asteroid_Type {
    ASTEROID_BIG,
    ASTEROID_MEDIUM,
    ASTEROID_SMALL
};

class Asteroid : public GameObject {

public:
    // Positioning
    glm::vec3 velocity;
    float direction;

private:
    bool alive = true;

public:
    Asteroid(float t_direction, glm::vec3 t_velocity);
    void update(Camera camera, float deltaTime);
    bool isAlive();
};
