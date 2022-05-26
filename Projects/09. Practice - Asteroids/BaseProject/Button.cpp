#include "Button.h"

Button::Button(std::vector<float> vertexData, std::vector<unsigned int> indexData, Shader shader, Image texture, glm::vec3 position) : GameObject(
    vertexData,
    indexData,
    shader,
    texture,
    position
    ) {
    
}

void Button::update(GLFWwindow* window, Camera* camera, glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
    update_pressed(window);

    std::cout << position.z << std::endl;
    

    view = glm::translate(view, position);

    
    shader.use();
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    glUseProgram(0);
}

bool Button::is_pressed() {
    return pressed;
}

void Button::update_pressed(GLFWwindow* window) {
    double xposd, yposd; glfwGetCursorPos(window, &xposd, &yposd);
    float xpos = static_cast<float> (xposd) / Settings::WIDTH; float ypos = static_cast<float> (yposd) / Settings::HEIGHT;

    // std::cout << position.x << " < " << xpos << " < " << position.x + vertSize.x << " " << ypos << std::endl;

    if (position.x + vertSize.x > xpos && position.x - vertSize.x < xpos
        && position.y + vertSize.y > ypos && position.y - vertSize.y < ypos) {
        pressed = true;
        return;
    }
    pressed = false;
}