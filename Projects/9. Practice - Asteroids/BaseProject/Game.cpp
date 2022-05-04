#include "Game.h"

Game::Game() {
    score = 0;
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
        player.move(SHIP_FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        player.move(SHIP_BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        player.move(SHIP_ROTATE_LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        player.move(SHIP_ROTATE_RIGHT, deltaTime);
}

void Game::update(GLFWwindow* window) {
    // updates deltaTime
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Rendering
    player.update(camera, deltaTime);
    player.draw();

    // Key Input
    handleInput(window);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

float Game::getDeltaTime() {
    return deltaTime;
}