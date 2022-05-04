#pragma once
#include <camera/camera.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Image.h"
#include "Settings.h"
#include "Ship.h"


class Game {

public:
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f));
    Ship player = Ship();

private:

    // delta time
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    int score;

public:
    Game();

    void run(GLFWwindow* window);

    void handleInput(GLFWwindow* window);

    void update(GLFWwindow* window);

    float getDeltaTime();
};