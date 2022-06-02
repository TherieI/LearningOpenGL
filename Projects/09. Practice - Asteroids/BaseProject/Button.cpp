#include "Button.h"

Button::Button(std::vector<float> vertexData, std::vector<unsigned int> indexData, Shader shader, Image texture, glm::vec3 position) : GameObject(
    vertexData,
    indexData,
    shader,
    texture,
    position
    ) {
    
}

void Button::update(GLFWwindow* window, glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
    update_mouse_hover(window);
    update_pressed(window);

    view = glm::translate(view, position);
    
    shader.use();
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    glUseProgram(0);
}

bool Button::is_pressed() {
    return pressed && mouse_hovering;
}

void Button::update_mouse_hover(GLFWwindow* window) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    double xposd, yposd; 
    glfwGetCursorPos(window, &xposd, &yposd);
    float xpos = static_cast<float> (xposd) / width; float ypos = static_cast<float> (yposd) / height;

    /*std::cout << xpos << " " << ypos << std::endl;
    std::cout << position.x << " " << position.y << std::endl;*/
    

    float dx, dy;
    dx = 0.5f + position.x / position.z;
    dy = 0.5f - position.y / position.z;

    if ((position.x + vertSize.x) / position.z + dx > xpos && (position.x - vertSize.x) / position.z + dx < xpos
        && (position.y + vertSize.y) / position.z + dy > ypos && (position.y - vertSize.y) / position.z + dy < ypos) {
        mouse_hovering = true;
        std::cout << "!";
        return;
    }
    mouse_hovering = false;
}

void Button::update_pressed(GLFWwindow* window) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        pressed = true;
        std::cout << "#";
        return;
    }
    pressed = false;
}