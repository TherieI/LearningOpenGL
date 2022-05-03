#include "Ship.h"

Ship::Ship() {
    shader = Shader("shaders/shape.vs", "shaders/color.fs");

    // Init Positions
    position = glm::vec3(0.0f, 0.0f, -10.0f);
    velocity = glm::vec3(0.0f);
    acceleration = glm::vec3(5.0f);
    direction = 90.0f;

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
    texture = Image("assets/ship1.png", GL_RGBA);
}

void Ship::move(Movement dir, float deltaTime) {
    float angle = glm::radians(direction);

    glm::vec3 dp = glm::vec3(0.0f);

    if (dir == SHIP_FORWARD) {
        dp.x = cosf(angle);
        dp.y = sinf(angle);
        velocity += dp * acceleration * deltaTime;
    }
    if (dir == SHIP_BACKWARD) {
        dp.x = -cosf(angle);
        dp.y = -sinf(angle);
        velocity += dp * acceleration * deltaTime;
    }
    if (dir == SHIP_ROTATE_LEFT) {
        direction += 270 * deltaTime;
    }
    if (dir == SHIP_ROTATE_RIGHT) {
        direction -= 270 * deltaTime;
    }
}

void Ship::update(Camera camera, float deltaTime) {
    // BINDING
    texture.use();  // Bind textures on corresponding texture units
    glBindVertexArray(VAO);  // Bind the VAO
    shader.use();  // Bind Shader

    // New position
    position += velocity * deltaTime;
    slow(deltaTime);
    inBounds();

    // Matrices
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, direction - 90, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 view = camera.GetViewMatrix();
    view = glm::translate(view, position);

    glm::mat4 projection = glm::perspective(90.0f, (float) Settings::WIDTH / Settings::HEIGHT, 0.1f, 100.0f);  // projection remains the same for all cubes

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


void Ship::slow(float deltaTime) {
    glm::vec3 unit = glm::normalize(velocity);
    if (abs(velocity.x) > 0) {
        velocity.x -= unit.x * acceleration.x / 4 * deltaTime;
    }
    if (abs(velocity.y) > 0) {
        velocity.y -= unit.y * acceleration.y / 4 * deltaTime;
    }
}

void Ship::inBounds() {
    std::cout << position.x << " " << position.y << std::endl;

    if (abs(position.x) > 20.0f) {
        position.x = -abs(position.x) / position.x * 20.0f;
    }
    if (abs(position.y) > 20.0f) {
        position.y = -abs(position.y) / position.y * 20.0f;
    }
}
