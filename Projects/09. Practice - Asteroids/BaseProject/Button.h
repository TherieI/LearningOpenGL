#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include <shaders/shader.h>
#include <camera/camera.h>

#include "Settings.h"
#include "GameObject.h"
#include "Image.h"

class Button : public GameObject {
public:
    Button(glm::vec3 position, Shader shader, Image image);
    void update(Camera* camera, float deltaTime);
    bool is_pressed();
};