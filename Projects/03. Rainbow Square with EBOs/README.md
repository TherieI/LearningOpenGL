### Shaders

Shaders are programs that run on the GPU. I had to write basic shaders when drawing a triangle in my previous project. In this section, I hope to go into more detail on them and the features they provide.

There are different shaders types dedicated to different purposes. The main shader types are the vertex, fragment, and geometry shaders. Vertex shaders typically effect position; fragment shaders determine color; and geometry shaders are optional, focused on vertex transformations. A shader follows this general structure:

```glsl
#version <version>

in <data type> <variable name>;
out <data type> <variable name>;

uniform <data type> <name>;

void main() {
    <an out variable> = data;
}
```



#### Uniforms

While vertex buffers appear to be used when transferring large amounts of data to GPU memory, uniforms are preferred when transferring small amounts of data from CPU to GPU. Unlike vertex attribute data, uniforms are *global* per shader program.

To create a uniform, we generate a location in a shader program using `glGetUniformLocation`, providing the *shader program* and the *variable name*. Then, we bind data using some function beginning with `glUnform*`. For example:

```cpp
float color[] = { 0.1f, 0.2f, 1.0f };  // Blue
int blueColorLocation = glGetUniformLocation(shaderProgram, "blueColor");  // generate the uniform location
glUniform3f(blueColorLocation, color[0], color[1], color[2]);  // assign a vec3 (float) to blueColor
```

In the GLSL file, we can access the uniform like such:

```glsl
// Fragment Shader
#version 330 core
out vec4 FragColor;
  
uniform vec4 blueColor;  // same variable used in glGetUniformLocation

void main()
{
    FragColor = blueColor;
}   
```



##### Coding Challenge - Glowing Rainbow Shader

About halfway through the [learnopengl shader][learngl_shader] section, I was inspired by the rainbow triangle shader with its unique RGB values that practically exploded from each vertex. I wanted to combine two of the examples - the rainbow shader and the "pulsing" shader, using uniforms to oscillate between different colors. I also wanted to create it with an EBO.

First, I defined the vertex data and indices.

```cpp
// VERTEX DATA
float vertices[] = {
    // positions         // colors
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
    0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   // top right
    -0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f    // top left

};
unsigned int indices[]{
    0, 1, 2,  // 1st triangle
    1, 2, 3,  // 2nd triangle
};
```

Then, I bound the the vertices and created an EBO.

```cpp
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

// Linking EBO to VBO
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

// Specifies the location and data format of the bound VBO to use when rendering
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
glEnableVertexAttribArray(1);

// Unbinding
glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);
```

I generated the uniform in the render loop, updating it based on GLFW time.

```cpp
// Bind the VAO
glBindVertexArray(VAO);

// Update time uniform
float timeValue = glfwGetTime();
int vertexColorLocation = glGetUniformLocation(triangleProgram, "timeValue");
glUseProgram(triangleProgram);
glUniform1f(vertexColorLocation, timeValue);

// Draw triangle
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

glBindVertexArray(0);
```

Finally, the shader code.

```glsl
// Vertex shader
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    color = aColor;
}
```

```glsl
// Fragment shader
#version 330 core
out vec4 FragColor;

uniform float timeValue;
in vec3 color;

void main()
{
    float x = (sin(timeValue + color.x) / 2.0f) + 0.5f;
    float y = (sin(timeValue + color.y) / 2.0f) + 0.5f;
    float z = (sin(timeValue + color.z) / 2.0f) + 0.5f;
    FragColor = vec4(x, y, z, 1.0f);
}
```

##### Source Code

```cpp
int main() {
    
    /* GLFW and GLAD initialization */

    // COMPILE AND CREATE SHADERS
    unsigned int vertexShader = compileShader(getShader("vertex.shader"), GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(getShader("fragment.shader"), GL_FRAGMENT_SHADER);
    unsigned int triangleProgram = glCreateProgram();
    glAttachShader(triangleProgram, vertexShader);
    glAttachShader(triangleProgram, fragmentShader);
    glLinkProgram(triangleProgram);
    glUseProgram(triangleProgram);

    // Deleting the shaders since they have been attached to the program and we no longer need them
    glDeleteShader(vertexShader);  
    glDeleteShader(fragmentShader);

    // VERTEX DATA
    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   // top right
        -0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f    // top left

    };
    unsigned int indices[]{
        0, 1, 2,  // 1st triangle
        1, 2, 3,  // 2nd triangle
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Unbinding
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // RENDER LOOP
    while (!glfwWindowShouldClose(window)) {
        // Key Input
        handleInput(window);

        // Rendering
        glClearColor(0.1f, 0.3f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind the VAO
        glBindVertexArray(VAO);

        // Update time uniform
        float timeValue = glfwGetTime();
        int vertexColorLocation = glGetUniformLocation(triangleProgram, "timeValue");
        glUseProgram(triangleProgram);
        glUniform1f(vertexColorLocation, timeValue);

        // Draw triangle
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
```

<img src="Documentation\4. Rendering\5. Rainbow Square Shader.gif" alt="5. Rainbow Square Shader" style="zoom: 50%;" />



#### Shader Class

Since I intend to document my learning of OpenGL in this project, I will not go over how to code the shader class, since it is composed of features that I previously explored, only streamlined into a C++ class. I transitioned to the shader class provided by [learnopengl][learngl_shader]. GLM, a library with OpenGL related mathematical functions, can be found [here][glm], as it is used in learnopengl's shader class.

The shader class handles all shader compilation and errors. It also provides functions for uniform creation.

```cpp
// Creating a shader program is reduced to this simple code
Shader program = Shader("shaders/vertex.shader", "shaders/fragment.shader");

// Enabling the program
program.use();

// Example uniform creation (program.set*())
program.setFloat("uniformName", 0.5f);
```

## 

[inputs]: https://www.khronos.org/opengl/wiki/Related_toolkits_and_APIs
[GLEW]: http://glew.sourceforge.net/index.html
[cherno]: https://www.youtube.com/watch?v=OR4fNpBjmq8
[learn]: https://learnopengl.com/Getting-started/OpenGL
[glfw]: https://www.glfw.org
[glfw_build]: https://learnopengl.com/Getting-started/Creating-a-window
[CMake]: https://cmake.org/download/
[linkerrorsolution]: https://stackoverflow.com/questions/39514632/error-cannot-open-file-kernel32-lib
[web interface]: https://glad.dav1d.de
[glad_error]: https://stackoverflow.com/questions/58460074/how-to-fix-unresolved-external-symbol-gladloadglloader-referenced-in-function
[docs_gl]: https://docs.gl
[window_code]: https://learnopengl.com/Getting-started/Hello-Window
[vbo_vao]: https://stackoverflow.com/questions/23314787/use-of-vertex-array-objects-and-vertex-buffer-objects
[glDrawElements]: https://docs.gl/gl4/glDrawElements
[learngl_shader]: https://learnopengl.com/Getting-started/Shaders
[glm]: https://github.com/Groovounet/glm
[GLM_WEB]: https://glm.g-truc.net/0.9.8/index.html
[GLM_DOWNLOAD]: https://github.com/g-truc/glm/releases/latest
[STB_DOWNLOAD]: https://github.com/nothings/stb
