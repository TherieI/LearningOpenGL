#include "Ship.h"

Ship::Ship() {
    shader = Shader("shaders/shape.vs", "shaders/color.fs");

    velocity = 10.0f;
    direction = 90.0;

    // VERTEX DATA
    float vertices[] = {
        // Positions          // Texture
        -0.5f, -0.5f,  0.0f,  0.0f, 0.0f, // BL
         0.5f, -0.5f,  0.0f,  1.0f, 0.0f, // BR
         0.5f,  0.5f,  0.0f,  1.0f, 1.0f, // TR
        -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, // TL
    };
    unsigned int indices[]{
        // Each triangle pair represents a side of a cube
        0,  1,  2,  // 1st triangle
        0,  2,  3,  // 2nd triangle
    };

    // Creating Objects to send to GPU
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Binding VAO 
    glBindVertexArray(VAO);

    // Adding vertices to VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Specifies the location and data format of the bound VBO to use when rendering
    // Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Textures
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbinding
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    texture = Image("assets/ship.png", GL_RGBA);
}

void Ship::move(Movement dir, float deltaTime) {
    float angle = glm::radians(direction);
    //cosf();
}

void Ship::update(Camera camera) {
    // BINDING
    texture.use();  // Bind textures on corresponding texture units
    glBindVertexArray(VAO);  // Bind the VAO
    shader.use();  // Bind Shader

    // Matrices
    model = glm::mat4(1.0f);
    view = camera.GetViewMatrix();
    projection = glm::perspective(90.0f, (float) Settings::WIDTH / Settings::HEIGHT, 0.1f, 100.0f);  // projection remains the same for all cubes

    // Uniforms
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    // Draw
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Unbinding
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}
