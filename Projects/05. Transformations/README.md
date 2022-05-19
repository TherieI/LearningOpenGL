# Transformations

Before we get into transformations, we want to install another helper-library. [GLM][GLM_WEB] (Open**GL** **M**athematics) is commonly used for matrix mathematics which is how we can move, rotate, and scale our elements. 

#### Adding GLM

1. Download the GLM files [here][GLM_DOWNLOAD] (or navigate through the GLM website until you find the source code).

2. |                          Step                          |                          Reference                           |
   | :----------------------------------------------------: | :----------------------------------------------------------: |
   |             Extract the zip and find `glm`             | <img src="Documentation\5. GLM\1.PNG" alt="1" style="zoom:67%;" /> |
   | Copy the `glm` root folder into your projects includes | <img src="Documentation\5. GLM\2.PNG" alt="2" style="zoom:67%;" /> |

3. Add these includes - they are the primary header files.

   ```cpp
   #include <glm/glm.hpp>
   #include <glm/gtc/matrix_transform.hpp>
   #include <glm/gtc/type_ptr.hpp>
   ```



#### First Transformations

Ideally, you'd want to understand matrix math. I lack knowledge on matrix math, so this section is mainly for messing around with values. That being said, there are three major matrices: the *projection*, *view*, and *model*. We define them like so:

```cpp
// Matrices
glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);
```

As of now there purposes are still vague to me, so lets fiddle with some numbers. We can do this by transforming the defined matrices with other GLM functions.

```cpp
// Transformations          
model = glm::rotate(model, /* Note that -55, this angle, is in degrees. */ -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));  
view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
projection = glm::perspective( /* Angle in degrees */ 45.0f, (float) WIDTH / (float) HEIGHT, 0.1f, 100.0f);
```

These are the starter transformations learnopengl provides us. Transforming matrices is great, but we have yet to send the data to the GPU. let's create uniforms to do so.

```cpp
// Creating the matrix uniform locations and transfering data
triangleProgram.setMat4("model", model);
triangleProgram.setMat4("view", view);
triangleProgram.setMat4("projection", projection);
```

On the GPU side of things:

```glsl
// Vertex Shader
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

// Matrices
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
```

```glsl
// Fragment Shader
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, TexCoord);
}
```

The result, combined with our other code, looks something like this:

<img src="Documentation\6. Transformations\1.PNG" alt="1" style="zoom:80%;" />



I could have read the documentation, but I think it's much more interesting to experiment yourself. I played around with values in the three aforementioned matrix transformation functions, and recorded my findings. This is what I determined:

```cpp
// Transformations          
model      = glm::rotate(model, angle °, direction *unit vec3);  
view       = glm::translate(view, relative position *vec3);
projection = glm::perspective(distance from camera?, aspect ratio, ?, ?);
```

The projection was the most difficult to figure out. I checked the documentation after, so here are the corrections:

```cpp
// Transformations          
model      = glm::rotate(model, angle °, direction *unit vec3);
view       = glm::translate(view, relative position *vec3);
projection = glm::perspective(fov °, aspect ratio, near, far);
```

To create loopy animations, we can incorporate GLFW's `glfwGetTime()` inside of a `sin()` function. By messing with values, I created the interesting animation below:

```cpp
int main() {
    
    /* GLFW and GLAD initialization */

    // COMPILE AND CREATE SHADERS
    Shader triangleProgram = Shader("shaders/vertex.shader", "shaders/fragment.shader");

    // VERTEX DATA
    float vertices[] = {
        // positions         // colors           // Textures
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int indices[]{
        0, 1, 2,  // 1st triangle
        0, 2, 3,  // 2nd triangle
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

    triangleProgram.setInt("texture1", 0);

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

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Activate shader
        triangleProgram.use();

        // Transforms
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        // glm::rotate(matrix, angle, direction);
        model = glm::rotate(model, (float)glfwGetTime() * 100, glm::vec3(sinf((float)glfwGetTime() * 10), 1.0f, sinf((float)glfwGetTime() * 10)));
        // glm::translate(matrix, relative position);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        // glm::projection(fov °, aspect ratio, near, far);
        projection = glm::perspective(45.0f, (float) WIDTH / (float) HEIGHT, 0.1f, 100.0f);

        // retrieve the matrix uniform locations
        triangleProgram.setMat4("model", model);
        triangleProgram.setMat4("view", view);
        triangleProgram.setMat4("projection", projection);

        // Bind the VAO
        glBindVertexArray(VAO);

        // Draw triangle
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
```

<img src="Documentation\6. Transformations\3.gif" alt="2" style="zoom:80%;" />



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