#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <shaders/shader.h>
#include <camera/camera.h>

#include "Settings.h"
#include "Image.h"

enum Movement {
    SHIP_FORWARD,
    SHIP_BACKWARD,
    SHIP_ROTATE_LEFT,
    SHIP_ROTATE_RIGHT
};

class Ship {
public:

    Shader shader;
    Image texture;
    unsigned int VBO, VAO, EBO;

    // Positioning
    float direction, velocity;
    glm::mat4 model, view, projection;

    Ship();
    void move(Movement dir, float deltaTime);
    void update(Camera camera);
};
