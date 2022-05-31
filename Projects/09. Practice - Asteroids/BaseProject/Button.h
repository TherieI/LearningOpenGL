#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include <shaders/shader.h>
#include <camera/camera.h>

#include "Settings.h"
#include "GameObject.h"
#include "Image.h"

class Button : public GameObject {
private:
    bool pressed = false;
    bool mouse_hovering = false;
public:
    Button(std::vector<float> vertexData, std::vector<unsigned int> indexData, Shader shader, Image texture, glm::vec3 position);
    void update(GLFWwindow* window, glm::mat4 model, glm::mat4 view, glm::mat4 projection);
    bool is_pressed();
private:
    void update_mouse_hover(GLFWwindow* window);
    void update_pressed(GLFWwindow* window);
};