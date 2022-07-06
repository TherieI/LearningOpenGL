#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shaders/shader.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Compute.h"

// Handles Window size changes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Handles user input
void handleInput(GLFWwindow* window);


const unsigned int WIDTH  = 1000;
const unsigned int HEIGHT = 1000;

int main() {
    // GLFW WINDOW HINTS
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  // supported version for GLSLv4.3
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
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // COMPILE AND CREATE SHADERS
    Shader textureShader = Shader("shaders/position.vs", "shaders/texture.fs");

    // Vertex Data
    float vertices[] = {
        // Positions        // Textures
        1.0f,  1.0f, 0.0f,  1.0f, 1.0f,   // Top Right
        1.0f, -1.0f, 0.0f,  1.0f, 0.0f,   // Bottom Right
       -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,   // Bottom Left
       -1.0f,  1.0f, 0.0f,  0.0f, 1.0f    // Top Left 
    };

    unsigned int indices[]{
        0, 1, 2,  // 1st Triangle
        0, 2, 3,  // 2nd Triangle
    };

    // Creating Objects to send to GPU
    unsigned int VBO, VAO, EBO;
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    // Texture Coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    // Credit: https://learnopengl.com/Guest-Articles/2022/Compute-Shaders/Introduction
    ComputeShader compute_shader("shaders/compute.cs", 10, 10, GL_TEXTURE0);

    // RENDER LOOP
    while (!glfwWindowShouldClose(window)) {
        
        // Computing texture using cs
        compute_shader.use();
        compute_shader.dispatch();
        compute_shader.wait();

        // Key Input
        handleInput(window);

        // Rendering
        glClearColor(0.1f, 0.3f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        textureShader.use();
        textureShader.setInt("tex", 0);

        // Draw triangle
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



