#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// learnopengl classes
#include <shaders/shader.h>
#include <camera/camera.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>


// Handles Window size changes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Handles user input
void handle_input(GLFWwindow* window);

// Interprets txt data to an int array
std::vector<int> get_data(const char* location);


// Screen settings
const unsigned int WIDTH  = 800;
const unsigned int HEIGHT = 600;


// delta time
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame


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
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // to be sorted
    std::vector<int> sortData = get_data("data.txt");

    float data_length = 2.0f / sortData.size();  // 2 = 1 - (-1)
    float max_height = *std::max_element(sortData.begin(), sortData.end());  // max in vector

    float rectangle []{
        // Positions                        // Color
         data_length / -2.0f, -1.0f,  0.0f,  1.0f, 0.0f, 0.0f,  // BL
         data_length /  2.0f, -1.0f,  0.0f,  1.0f, 0.0f, 0.0f,  // BR
         data_length /  2.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,  // TR
         data_length / -2.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,  // TL
    };

    unsigned int indices[]{
        // Each triangle pair represents a side of a cube
        0,  1,  2,  // 1st triangle
        0,  2,  3,  // 2nd triangle
    };

    // COMPILE AND CREATE SHADERS
    Shader elementShader = Shader("shaders/shape.vs", "shaders/color.fs");


    // Creating Objects to send to GPU
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Binding VAO 
    glBindVertexArray(VAO);

    // Adding vertices to VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // Specifies the location and data format of the bound VBO to use when rendering
    // Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    // Colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    
    // Unbinding
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // RENDER LOOP
    while (!glfwWindowShouldClose(window)) {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Key Input
        handle_input(window);

        // Rendering
        glClearColor(0.1f, 0.3f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Activate shader
        elementShader.use();

        // Bind the VAO
        glBindVertexArray(VAO);

        // create transformations
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        float dx = -1.0f + data_length/2;
        for (int i : sortData) {
            model = glm::mat4(1.0f);
            view = glm::mat4(1.0f);
            projection = glm::mat4(1.0f);

            view = glm::translate(view, glm::vec3(dx, 0.0f, 0.0f));
            dx += data_length;
            
            float height = i / max_height;

            elementShader.setFloat("height", height);
            elementShader.setMat4("model", model);
            elementShader.setMat4("view",  view);
            elementShader.setMat4("projection", projection);

            // Draw triangle
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        

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

void handle_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

std::vector<int> get_data(const char* location) {
    std::vector<int> data;
    std::string dataString;

    std::ifstream dataFile;
    // ensure ifstream objects can throw exceptions:
    dataFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        dataFile.open(location);
        std::stringstream dataStream;
        // read file's buffer contents into streams
        dataStream << dataFile.rdbuf();
        // close file handlers
        dataFile.close();
        // convert stream into string
        dataString = dataStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR reading text data " << e.what() << std::endl;
    }

    std::string delimiter = ", ";

    size_t pos = 0;
    std::string token;
    while ((pos = dataString.find(delimiter)) != std::string::npos) {
        token = dataString.substr(0, pos);
        data.push_back(stoi(token));
        dataString.erase(0, pos + delimiter.length());
    }
    return data;
}