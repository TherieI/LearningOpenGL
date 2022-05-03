#include "GameObject.h"

GameObject::GameObject(std::vector<float> vertexData, std::vector<unsigned int> indexData, Shader shader, Image texture) {

    std::cout << "SIZE: " << vertexData.size();

    vertexData = {
        // Positions          // Texture
        -0.5f, -0.5f,  0.0f,  0.0f, 0.0f, // BL
         0.5f, -0.5f,  0.0f,  1.0f, 0.0f, // BR
         0.5f,  0.5f,  0.0f,  1.0f, 1.0f, // TR
        -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, // TL
    };

    std::cout << "SHADER ID " << shader.ID;

    indexData = {
        // Each triangle pair represents a side of a cube
        0,  1,  2,  // 1st triangle
        0,  2,  3,  // 2nd triangle
    };

    std::cout << "SIZE: " << vertexData.size();

    indices = indexData;

    // Creating Objects to send to GPU
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Binding VAO 
    glBindVertexArray(VAO);

    // Adding vertices to VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), &vertexData[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(unsigned int), &indexData[0], GL_STATIC_DRAW);

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

    // Texture and shader
    this->shader = shader;
    this->texture = texture;
}

void GameObject::update(Camera camera, float deltaTime) {  // Override to do your own transformations
    // Matrices
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(90.0f, (float)Settings::WIDTH / Settings::HEIGHT, 0.1f, 100.0f);  // projection remains the same for all cubes

    // Uniforms
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
}

void GameObject::draw() {
    bindAll();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);  // Draw
    unbindAll();
}

void GameObject::bindAll() {
    glBindVertexArray(VAO);  // Bind the VAO
    shader.use();  // Bind Shader
    texture.use();  // Bind textures on corresponding texture units
}

void GameObject::unbindAll() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}