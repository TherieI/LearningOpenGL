#include "Game.h"

Game::Game(int width, int height) {
    score = 0;
    this->width = width;
    this->height = height;
}

void Game::run(GLFWwindow* window) {
    // gaming mode
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::handleInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void Game::update(GLFWwindow* window, Ship player) {
    // updates deltaTime
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    player.texture.use();

    // Bind the VAO
    glBindVertexArray(player.VAO);

    // Key Input
    handleInput(window);

    // Rendering
    glClearColor(0.1f, 0.3f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    player.shader.use();

    // Matrices
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(90.0f, (float)width / height, 0.1f, 100.0f);  // projection remains the same for all cubes

    // Uniforms
    player.shader.setMat4("model", model);
    player.shader.setMat4("view", view);
    player.shader.setMat4("projection", projection);

    // Draw triangle
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
}