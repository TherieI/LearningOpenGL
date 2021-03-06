#pragma once
#include <camera/camera.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Image.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "Settings.h"
#include "Ship.h"
#include "Projectile.h"
#include "Asteriod.h"


class Game {

public:
    Camera* camera;
    Ship player = Ship();
    std::vector<Asteroid> asteroids{};
    std::vector<Projectile> projectiles{};
    float cooldown = 0.0f;

private:

    // delta time
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame
    int level = 0;
    int score;

public:
    Game(Camera *camera);
    void reload();
    void handleInput(GLFWwindow* window);
    void update(GLFWwindow* window);
    void spawnAsteroid(Asteroid_Type asize);
    void spawnAsteroid(Asteroid_Type asize, glm::vec3 pos);
    void checkState();
    float getDeltaTime();

private:
    void updateProjectiles();
    void updateCooldown();
    void shoot(Projectile_Type ptype);
    void updateAsteroids();
};