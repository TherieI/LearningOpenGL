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
private:  
    // The stuff has values but they dont get defined???/
    std::vector<float> _vertexData {
        // Positions          // Texture
        -0.5f, -0.5f,  0.0f,  0.0f, 0.0f, // BL
         0.5f, -0.5f,  0.0f,  1.0f, 0.0f, // BR
         0.5f,  0.5f,  0.0f,  1.0f, 1.0f, // TR
        -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, // TL
    };
    std::vector<unsigned int> _indexData {
        // Each triangle pair represents a side of a cube
        0,  1,  2,  // 1st triangle
        0,  2,  3,  // 2nd triangle
    };
    Shader _shader = Shader("shaders/shape.vs", "shaders/color.fs");
    Image _texture = Image("assets/ship1.png", GL_RGBA);

public:

    // Positioning
    glm::vec3 position, velocity, acceleration;
    float direction;

    Ship(std::vector<float> vertexData, std::vector<unsigned int> indexData, Shader shader, Image texture);
    void move(Movement dir, float deltaTime);
    void update(Camera camera, float deltaTime);

private:
    void slow(float deltaTime);
    void inBounds();
};
