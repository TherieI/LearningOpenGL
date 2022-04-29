#ifndef SHIP_H // include guard
#define SHIP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// STB
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>

#include <shaders/shader.h>

class Ship {
public:

    Shader shader = Shader("shaders/shape.vs", "shaders/color.fs");
    unsigned int VBO, VAO, EBO;
    unsigned int textureID;

    Ship() {
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

        // Getting textures
        stbi_set_flip_vertically_on_load(true);
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Enabling PNG transparency
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // load and generate the texture
        int width, height, nrChannels;
        unsigned char* data = stbi_load("assets/ship.png", &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    void handleInput() {

    }
};

#endif