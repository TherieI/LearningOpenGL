#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include <shaders/shader.h>
#include <camera/camera.h>

#include "Settings.h"
#include "GameObject.h"
#include "Image.h"

enum Movement {
    SHIP_FORWARD,
    SHIP_BACKWARD,
    SHIP_ROTATE_LEFT,
    SHIP_ROTATE_RIGHT
};

class Ship : public GameObject {

public:
    // Positioning
    glm::vec3 velocity, acceleration;
    float direction;

    Ship();
    void move(Movement dir, float deltaTime);
    void update(Camera camera, float deltaTime);

private:
    void slow(float deltaTime);
};
