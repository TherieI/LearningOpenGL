#pragma once
#include <glad/glad.h>
#include <shaders/shader.h>
#include "Image.h"


class Ship {
public:

    Shader shader;
    Image texture;
    unsigned int VBO, VAO, EBO;

    Ship();
    void handleInput();
};
