#include "Button.h"

Button::Button(glm::vec3 position, Shader shader, Image image) : GameObject(
    {
        // Positions          // Texture
        -1.0f, -0.33f,  0.0f,  0.0f, 0.0f, // BL
         1.0f, -0.33f,  0.0f,  1.0f, 0.0f, // BR
         1.0f,  0.33f,  0.0f,  1.0f, 1.0f, // TR
        -1.0f,  0.33f,  0.0f,  0.0f, 1.0f, // TL
    },
    {
            0,  1,  2,  // 1st triangle
            0,  2,  3,  // 2nd triangle
    },
    shader,
    image,
    position
    ) {
    
}

void Button::update(Camera* camera, float deltaTime) {

}

bool Button::is_pressed() {
    return false;
}