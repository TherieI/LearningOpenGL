#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shaders/shader.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

// Handles Window size changes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Handles user input
void handleInput(GLFWwindow* window);


const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;


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


    // COMPILE AND CREATE SHADERS
    Shader triangleProgram = Shader("shaders/vertex.shader", "shaders/fragment.shader");

    // VERTEX DATA
    float vertices[] = {
        // positions         // colors         
       -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // top left
        0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // bottom left
    };
    unsigned int indices[]{
        0, 1, 2,  // 1st triangle
        0, 2, 3,  // 2nd triangle
    };

    // Creating buffers to store our vertex data and index data 
    // Wrapping those buffers in a vertex array to attribute the data
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Binding VAO 
    glBindVertexArray(VAO);

    // Storing the contents of "vertices" in VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Adding pointers to different positions of vertices to distinguish the meaning behind the data
    // Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbinding
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // RENDER LOOP
    while (!glfwWindowShouldClose(window)) {
        handleInput(window);

        // Set a background color and 
        glClearColor(0.1f, 0.3f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Calls glUseProgram, binding our shaders
        triangleProgram.use();

        // Bind the Vertex Array Object so the program will use VAO's vertex data
        glBindVertexArray(VAO);

        // Render based on our index data, calling glDrawElements instead of glDrawArrays
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void handleInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        std::cout << "Space pressed\n";
    }
}



