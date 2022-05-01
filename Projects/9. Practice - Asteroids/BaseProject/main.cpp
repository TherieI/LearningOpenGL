#include "main.h"

#include "Game.h"
#include "Ship.h"

// Screen settings
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

// Handles Window size changes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


int main() {
    // GLFW WINDOW HINTS
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLFW WINDOW CREATION
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "The Real", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // GLAD INIT
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // The game
    Game game = Game(WIDTH, HEIGHT);
    game.handleInput(window);

    // Player
    Ship player = Ship();

    // RENDER LOOP
    while (!glfwWindowShouldClose(window)) {

        game.update(window, player);
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}