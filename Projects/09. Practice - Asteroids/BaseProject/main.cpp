#include "main.h"

int main() {
    // GLFW WINDOW HINTS
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLFW WINDOW CREATION
    GLFWwindow* window = glfwCreateWindow(Settings::WIDTH, Settings::HEIGHT, "Asteroids", NULL, NULL);
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

    // -----------------------------------------------------------------------------
    
    GameState state = MENU;
    
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 10.0f));

    Menu menu = Menu(&camera);

    Game game = Game(&camera);
    game.reload();

    GameObject background = GameObject(
        {
            // Positions          // Texture
            -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, // BL
             1.0f, -1.0f,  0.0f,  1.0f, 0.0f, // BR
             1.0f,  1.0f,  0.0f,  1.0f, 1.0f, // TR
            -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, // TL
        },
        {
             0,  1,  2,  // 1st triangle
             0,  2,  3,  // 2nd triangle
        },
        Shader("shaders/background.vs", "shaders/background.fs"),
        Image("assets/background.png", GL_RGBA),
        glm::vec3(0.0f, 0.2f, camera.Position.z - 1.0f)
    );
    background.update(&camera);  // background is static so only needs to be updated once

    // RENDER LOOP
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        background.draw();

        switch (state) {
        case MENU:
            menu.update(window, 0);
            if (menu.game_started()) {
                state = GAME;
            }
            break;
        case GAME:
            game.update(window);
            break;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    /*Settings::WIDTH = width;
    Settings::HEIGHT = height;*/
}