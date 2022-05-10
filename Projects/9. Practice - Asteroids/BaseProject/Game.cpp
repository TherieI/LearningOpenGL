#include "Game.h"

Game::Game() {
    score = 0;
    srand(time(NULL));
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
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        shoot(PROJECTILE_PLAYER);
}

void Game::update(GLFWwindow* window) {
    // updates deltaTime
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // update projectiles
    updateProjectiles();
    updateAsteroids();
    updateCooldown();

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

void Game::updateProjectiles() {
    // std::cout << projectiles.size() << std::endl;

    for (int i = projectiles.size() - 1; i >= 0; i--) {
        projectiles[i].update(camera, deltaTime);
        projectiles[i].draw();

        // Check collisions with asteroids
        for (int j = asteroids.size() - 1; j >= 0; j--) {
            if (projectiles[i].collideswith(asteroids[j])) {
                asteroids[j].destroy();
                projectiles[i].destroy();
                break;
            }
        }

        if (!projectiles[i].isAlive()) {
            projectiles.erase(projectiles.begin() + i);
        }
    }
}

void Game::updateCooldown() {
    if (cooldown > 0) {
        cooldown -= deltaTime;
    }
}

void Game::shoot(Projectile_Type ptype) {
    if (cooldown > 0) {
        return;
    }
    cooldown = 0.25f;
    Projectile p = Projectile(player.direction, player.position, ptype);
    projectiles.push_back(p);
}

void Game::spawnAsteroid(Asteroid_Type asize) {
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);  // random float between 0 and 1
    float angle = r * 360;

    r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float xPos = (r * 20) - 10.0f;

    r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float yPos = (r * 20) - 10.0f;

    Asteroid a = Asteroid(angle, glm::vec3(xPos, yPos, Settings::ENTITY_DEPTH), asize);
    asteroids.push_back(a);
}

void Game::updateAsteroids() {
    for (int i = asteroids.size() - 1; i >= 0; i--) {
        asteroids[i].update(camera, deltaTime);
        asteroids[i].draw();

        if (!asteroids[i].isAlive()) {
            asteroids.erase(asteroids.begin() + i);
        }
    }
}