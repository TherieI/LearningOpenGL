# Textures

If you're familiar with videogames, you will know that colors aren't the only thing that can be drawn to the screen. While textures can be commutated mathematically, it is much easier to use an image, such as a *png* or *jpg*. Texture data can be mapped to vertices in OpenGL, known as "texture coordinates".  

Here are some vertex positions that ultimately create a rectangle on the screen.

```cpp
float vertices[] = {
    // Positions
    0.5f,  0.5f, 0.0f,  // Top Right
    0.5f, -0.5f, 0.0f,  // Bottom Right
   -0.5f, -0.5f, 0.0f,  // Bottom Left
   -0.5f,  0.5f, 0.0f,  // Top Left 
};
unsigned int indices[]{
    0, 1, 2,  // 1st Triangle
    0, 2, 3,  // 2nd Triangle
};
```

Images are mapped by values from `[0.0f, 1.0f]` in both the x and y directions. Lets try and map the *Top Right* vertex to the *Top Right* of an image.

```cpp
float vertices[] = {
    // Positions       // Textures
    0.5f, 0.5f, 0.0f,  1.0f, 1.0f,   // Top Right
    
    /* Excluded Vertices */
};
```

And then the rest.

```cpp
float vertices[] = {
    // Positions        // Textures
    0.5f,  0.5f, 0.0f,  1.0f, 1.0f,   // Top Right
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f,   // Bottom Right
   -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   // Bottom Left
   -0.5f,  0.5f, 0.0f,  0.0f, 1.0f    // Top Left 
};

unsigned int indices[]{
    0, 1, 2,  // 1st Triangle
    0, 2, 3,  // 2nd Triangle
};
```

Hopefully, though brief, this explanation makes sense. Now we roughly understand texture coordinates, but how do we actually add images?

#### Loading Images

`stb_image.h` is a popular library by Sean Barrett that deals with common file formats. Like other libraries we need to download and add them to our project files.

1. Download [stb_image.h][STB_DOWNLOAD]

2. |                             Step                             |                          Reference                           |
   | :----------------------------------------------------------: | :----------------------------------------------------------: |
   |        Extract `stb-master` and locate `stb_image.h`         | <img src="Documentation\4. Rendering\STB Textures\1.PNG" alt="1" style="zoom:67%;" /> |
   | Copy `stb_image.h` and add it to your project's includes folder<br />I like to have it in an `stb` folder, like so `..includes/stb/stb_image.h` | <img src="Documentation\4. Rendering\STB Textures\2.PNG" alt="2" style="zoom:67%;" /> |

3. Add the include of the header file. **NOTE**- you need to define `STB_IMAGE_IMPLEMENTATION` before including `stb_image.h`

   ```cpp
   #define STB_IMAGE_IMPLEMENTATION
   #include <stb/stb_image.h>
   ```



Now that we have functions to load images, we can add them to our project.

```cpp
// Getting Texture
stbi_set_flip_vertically_on_load(true);
// Generating a texture like we would a buffer
unsigned int texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);

// Setting the texture wrapping/filtering options (on the currently bound texture object)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// Loading and generating the texture
int width, height, nrChannels;
unsigned char* data = stbi_load("image.jpg", &width, &height, &nrChannels, 0);
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
```

In our shaders...

```glsl
// Vertex Shader
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
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

In the render loop...

```cpp
while (!glfwWindowShouldClose(window)) {
        
    /* Key Input and Clearing */

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    /* Drawing Triangles */
}
```

<img src="Documentation\4. Rendering\6. Gigachad Texture.PNG" alt="6. Gigachad Texture" style="zoom:80%;" />





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