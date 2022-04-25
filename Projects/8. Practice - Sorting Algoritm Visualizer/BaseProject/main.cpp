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
#include <string>
#include <fstream>
#include <sstream>


// Handles Window size changes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Handles user input
void handle_input(GLFWwindow* window);

// Handles mouse input
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// Interprets txt data to an int array
std::vector<int> get_data(const char* location);


// Screen settings
const unsigned int WIDTH  = 800;
const unsigned int HEIGHT = 600;

// Camera
Camera camera = Camera(glm::vec3(0.0f, 0.0f, 10.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

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

    // Enable depth test for 3D
    glEnable(GL_DEPTH_TEST);

    // gaming mode
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    // to be sorted
    std::vector<int> nums = get_data("data.txt");

    // COMPILE AND CREATE SHADERS
    Shader triangleProgram = Shader("shaders/shape.vs", "shaders/color.fs");

    // VERTEX DATA
    float vertices[] = {
        // Positions          // Colors          // Texture
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // 1 1
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // 1 0
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, // 1 1
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // 0 1 

        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // 1 1
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // 1 0
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, // 1 1
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // 0 1

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // 1 1
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // 1 0
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, // 1 1
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // 0 1

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // 1 1
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // 1 0
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, // 1 1
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // 0 1   

        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // 1 1
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // 1 0
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, // 1 1
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // 0 1  

        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // 1 1
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // 1 0
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, // 1 1
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // 0 1   
    };
    unsigned int indices[]{
         // Each triangle pair represents a side of a cube
         0,  1,  2,  // 1st triangle
         0,  2,  3,  // 2nd triangle

         4,  5,  6,  // 1st triangle
         4,  6,  7,  // 2nd triangle

         8,  9, 10,  // 1st triangle
         8, 10, 11,  // 2nd triangle

        12, 13, 14,  // 1st triangle
        12, 14, 15,  // 2nd triangle

        16, 17, 18,  // 1st triangle
        16, 18, 19,  // 2nd triangle

        20, 21, 22,  // 1st triangle
        20, 22, 23,  // 2nd triangle
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    // Colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Textures
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    // Unbinding
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Getting textures
    stbi_set_flip_vertically_on_load(true);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load("gigachad.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // Practice - Pan around Gigachad Planets
    // RENDER LOOP
    while (!glfwWindowShouldClose(window)) {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Key Input
        handle_input(window);

        // Rendering
        glClearColor(0.1f, 0.3f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate shader
        triangleProgram.use();

        // Bind the VAO
        glBindVertexArray(VAO);
        

        // Matrices
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(45.0f, (float) WIDTH / HEIGHT, 0.1f, 100.0f);  // projection remains the same for all cubes

        // Transforms
        // Rotation
        glm::vec3 rotDir;
        float rotVelocity;
        // Position
        float velocity;

        // Cube 1 (Center)

        // Rotations
        rotDir = glm::vec3(0.3f, 0.7f, 0.2f);
        rotVelocity = 20.0f;
        // Position
        glm::vec3 cube1Pos = glm::vec3(0.0f, 0.0f, 0.0f);;

        // Transforms
        model = glm::rotate(model, (float) glfwGetTime() * rotVelocity, rotDir);
        view = glm::translate(view, cube1Pos);

        // Uniforms
        triangleProgram.setMat4("model", model);
        triangleProgram.setMat4("view", view);
        triangleProgram.setMat4("projection", projection);

        // Draw triangle
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        // Cube 2 (Rotating around Cube 1)

        // Matrices
        model = glm::mat4(1.0f);
        view = camera.GetViewMatrix();

        // Rotations
        rotDir = glm::vec3(0.5f, 0.2f, 0.4f);
        rotVelocity = 50.0f;
        // Position
        velocity = 3.0f;
        glm::vec3 cube2Pos = glm::vec3(sin((float)glfwGetTime() * velocity) * 4, cos((float)glfwGetTime() * velocity) * 2, -cos((float)glfwGetTime() * velocity) * 8) + cube1Pos;

        // Transforms
        model = glm::rotate(model, (float) glfwGetTime() * rotVelocity, rotDir);
        view = glm::translate(view, cube2Pos);

        // Uniforms
        triangleProgram.setMat4("model", model);
        triangleProgram.setMat4("view", view);
        triangleProgram.setMat4("projection", projection);

        // Draw triangle
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        // Cube 3 (Rotating around Cube 1)

        // Matrices
        model = glm::mat4(1.0f);
        view = camera.GetViewMatrix();

        // Rotations
        rotDir = glm::vec3(0.1f, 0.2f, 0.9f);
        rotVelocity = 100.0f;
        // Position
        velocity = 2.0f;
        glm::vec3 cube3Pos = glm::vec3(sin((float)glfwGetTime() * velocity) * 8, cos((float)glfwGetTime() * velocity) * 2, cos((float)glfwGetTime() * velocity) * 10) + cube1Pos;

        // Transforms
        model = glm::rotate(model, (float)glfwGetTime() * rotVelocity, rotDir);
        view = glm::translate(view, cube3Pos);

        // Uniforms
        triangleProgram.setMat4("model", model);
        triangleProgram.setMat4("view", view);
        triangleProgram.setMat4("projection", projection);

        // Draw triangle
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

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

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
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