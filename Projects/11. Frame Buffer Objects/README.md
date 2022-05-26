# Boilerplate OpenGL project



Getting started is often the hardest part of learning something new. In this project, I downloaded the necessary files and dependencies to create a window in OpenGL. 



## OpenGL Theory

This is a section where I compile useful information I've found on the internet in understanding the abstracts of OpenGL. I am currently using [this][learn] website to learn OpenGL.

OpenGL is an API that provides us with the links to our GPU's graphics functions. A prime misconception is that we install OpenGL. This is wrong: OpenGL functions are implemented by our graphics card manufacturer. What we need to download are APIs that can manage [inputs][], handle [windows][glfw], and perhaps some that make working with cross-platform easier. 

If we already have OpenGL functions, how do we access them? Since there are many different versions of OpenGL drivers, the location of most of its functions is not known at compile-time and needs to be queried at run-time. Though we could find these locations and manually link them, the easier option is to install a library that provides the links for us, for example, [GLEW][]. GLEW finds functions that are supported on our graphics cards and loads them to a C++ header file, which allows us to call them. [This][cherno] video is a great resource to follow if you are interested in installing `GLFW` and `GLEW`.



### Core-Profile and Immediate Mode

| Core-Profile                                                 | Immediate Mode                                               |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| More flexible<br />More features<br />More control<br />Efficient<br />Modern | "Legacy" Mode<br />Simpler, but hides a lot of advanced functionality<br />Inefficient<br />Deprecated features<br /> |



### State Machine

OpenGL is ultimately a collection of variables that define how it should operate. The state of OpenGL is often referred to as the **context**. For example, if we wanted to switch from drawing triangles to drawing lines, the code might **look** something like: `glSetDrawState(GL_TRIANGLE, context)` (but wouldn't actually be that).



### Objects

Objects in OpenGL are written in C but allow many derivations for other languages. An OpenGL object is a collection of **options** that represent a **subset** of OpenGL's state. 



### Creating a Window

Before creating graphics, we need to create a window to draw in. However, creating windows are specific per operating system. OpenGL tries to abstract itself from creating windows, meaning it is preferred to use an external library. [GLFW][glfw] is a library, written in C, that handles windows across multiple platforms. Whether it be Mac, Linux, or Windows, we can count on GLFW to sort out our windows and handle input so we can work on graphics.



#### Building GLFW

In this section, I attempted to build GLFW without using the precompiled binaries. In other words, I compiled the source code myself. [Here][glfw_build] is the tutorial I followed. Though you can download the binaries pre-compiled, it is good practice to build them yourself.

1. [Download][glfw] the source code. Take note of the location you saved the source code to, since we will need it for CMake.

2. Install [CMake][].
   *CMake is a tool that can generate project/solution files of a user's choice. Then we can compile those files in the solution. Eg. a Visual Studio solution.*

   |                             Step                             |                          Reference                           |
   | :----------------------------------------------------------: | :----------------------------------------------------------: |
   | `Run` CMake<br />Add `source`[^1] and `output`[^2] folder locations<br />Click `Configure` | <img src="Documentation\1. CMake\1.PNG" alt="1" style="zoom:67%;" /> |
   |   Enter *your* Visual Studio version.<br />Click `Finish`    | <img src="Documentation\1. CMake\2.PNG" alt="2" style="zoom: 50%;" /> |
   | Here we can decide what files to generate. I recommend leaving the defaults.<br />Click `Generate` | <img src="Documentation\1. CMake\3.PNG" alt="3" style="zoom:50%;" /> |
   | Open the Visual Studio Solution that was generated in the root destination folder. | <img src="Documentation\1. CMake\4.PNG" alt="4" style="zoom:50%;" /> |
   |                    Click `Build Solution`                    | <img src="Documentation\1. CMake\5.PNG" alt="5" style="zoom: 50%;" /> |
   |          The library should be built in `src/Debug`          |     <img src="Documentation\1. CMake\6.PNG" alt="6"  />      |

   [^1]: The source should be the root folder of GLFW
   [^2]: The output can be any location



#### Setting up GLFW in Visual Studio

Now that we have `glfw3.lib` compiled, we can set up our first project. There are two main steps we need to complete: 1) Creating a project and 2) linking our dependencies. There are different ways of linking our dependencies, but from what I've noted, and what [learnopengl][learn] recommends, is to create a `dependencies` directory with two sub-directories, `dependencies/includes` for header files and `dependencies/lib` for libraries such as `glfw3.lib`. Then we can reference these locations in Visual Studio settings.

|                             Step                             |                          Reference                           |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
|                `Create` an Empty C++ Project                 | <img src="Documentation\2. Setting up a VS Project\1.PNG" alt="1" style="zoom:50%;" /> |
|       Name it anything, locate it anywhere convenient        | <img src="Documentation\2. Setting up a VS Project\2.PNG" alt="2" style="zoom:50%;" /> |
| In the root of your newly created project, create a folder called `dependencies`<br />The root directory should have the `<your project>.sln` file | <img src="Documentation\2. Setting up a VS Project\3.PNG" alt="3" style="zoom:80%;" /> |
| In this dependencies folder, create subfolders for includes and library files | <img src="Documentation\2. Setting up a VS Project\4.PNG" alt="4" style="zoom:80%;" /> |
| In the source GLFW folder, navigate to `include`<br />Copy the folder `GLFW`<br />Paste it into `<your VS project>/dependencies/includes` | <img src="Documentation\2. Setting up a VS Project\5.PNG" alt="5" style="zoom: 80%;" /> |
| In our compiled GLFW folder, navigate to `src/Debug`<br />Copy `glfw3.lib`<br />Paste it into `<your VS project>/dependencies/lib` | <img src="Documentation\2. Setting up a VS Project\6.PNG" alt="6" style="zoom:80%;" /> |
|     Right-click your VS project and select `Properties`      | <img src="Documentation\2. Setting up a VS Project\7.PNG" alt="7" style="zoom: 67%;" /> |
| In `Configuration Properties/VC++ Directories`, edit `Include Directories` | <img src="Documentation\2. Setting up a VS Project\8.PNG" alt="8" style="zoom: 50%;" /> |
| Add `$(SolutionDir)dependencies\includes` as an extra directory<br />Click `OK` | <img src="Documentation\2. Setting up a VS Project\9.PNG" alt="9" style="zoom: 80%;" /> |
| In `Configuration Properties/VC++ Directories`, edit `Library Directories` | <img src="Documentation\2. Setting up a VS Project\10.PNG" alt="10" style="zoom:80%;" /> |
| Add `$(SolutionDir)dependencies\lib` as an extra directory<br />Click `OK` | <img src="Documentation\2. Setting up a VS Project\11.PNG" alt="11" style="zoom:80%;" /> |
| In `Configuration Properties/Linker/Input`, edit `Additional Dependencies` | <img src="Documentation\2. Setting up a VS Project\12.PNG" alt="12" style="zoom:80%;" /> |
| Add `glfw3.lib` (which you compiled) and `opengl32.lib` (that comes with Visual Studio)<br />Click `OK` | <img src="Documentation\2. Setting up a VS Project\13.PNG" alt="13" style="zoom:80%;" /> |
| Right-click your VS project and select `Properties/Add/New Item...` | <img src="Documentation\2. Setting up a VS Project\14.PNG" alt="14" style="zoom: 50%;" /> |
|                      Create a C++ file                       | <img src="Documentation\2. Setting up a VS Project\15.PNG" alt="15" style="zoom:67%;" /> |
| Now you should be able to add `include <GLFW/glfw3.h>` without any reference errors | <img src="Documentation\2. Setting up a VS Project\16.PNG" alt="16"  /> |

##### GLFW Problems

After completing the steps above, I tried to build the project but received the error `fatal error LNK1104: cannot open file 'opengl32.lib'`. This was due to a linking error, but I did not know where `opengl32.lib` was because I assumed it came with Visual Studio. Turns out, it did. All I needed to do was add `$(VC_IncludePath)` and `$(WindowsSDK_IncludePath)` in `VC++ Directories/Include Directories` as other include directories, and add `$(VC_LibraryPath_x86)` and `$(WindowsSDK_LibraryPath_x86)` in `VC++ Directories/Library Directories` as other library directories. Here is the [source][linkerrorsolution] that helped me solve the problem.



#### Setting up GLAD in Visual Studio

As I mentioned in my *OpenGL theory* intro, OpenGL's functions are already embedded in our system. We just need to point to them in our C++ code. If we were to manually retrieve locations of each function, the code would look something like this:

```cpp
// define the function's prototype
typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
// find the function and assign it to a function pointer
GL_GENBUFFERS glGenBuffers  = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
// function can now be called as normal
unsigned int buffer;
glGenBuffers(1, &buffer);
```

*Sample code from [learnopengl][glfw_build]*

If I've learnt anything about programmers, its that we avoid extra effort whenever possible. GLAD is a service provided by some kind souls that have automated this retrieval processes for us. We can request relevant OpenGL function definitions in the GLAD [web interface][], such as version-specific or core functions.

|                             Step                             |                          Reference                           |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| Go to the GLAD web interface<br />Select `C/C++` for Language<br />Select `OpenGL` for Specification<br />Select a `GL version` above `3.3`<br />Select `Core` for Profile<br />Select `Generate a loader`<br />(Optional) Add the extensions<br />`GENERATE` | <img src="Documentation\3. GLAD\1.PNG" alt="1" style="zoom: 50%;" /> |
|                     Download `glad.zip`                      | <img src="Documentation\3. GLAD\2.PNG" alt="2" style="zoom: 50%;" /> |
|                      Extract the files                       | <img src="Documentation\3. GLAD\3.PNG" alt="3" style="zoom: 150%;" /> |
| In your Visual Studio project, add the contents of `glad/include`  (`glad` and `KHR`) to your includes dependency folder | <img src="Documentation\3. GLAD\4.PNG" alt="4" style="zoom:80%;" /> |
| Add `glad.c` from `glad/src` to your Visual Studio project files<br />*Note:* You also need to add `glad.c` as a "new item" in Visual Studio | <img src="Documentation\3. GLAD\5.PNG" alt="5" style="zoom:80%;" /> |

##### GLAD Problems

After running the `Local Windows Debugger`, I got the error `library machine type 'x64' conflicts with target machine type 'x86'`. I compiled and set up the project for `64-bit`, but I accidently ran the debugger in `32-bit` mode. After swapping to `64-bit` mode, I found my include directories unlinked. I had to go back into the project properties and add my `include` and `lib` directories to `VC++ Directories`, then add back the missing `glfw3.lib` and `opengl32.lib` to the linker.

If building the project does not produce any more errors, then we can move on to the next step.



### Programming a Window

*[docs.gl][docs_gl] provides the official documentation for OpenGL functions. For extra information on a GL function, feel free to reference it.*

Add the includes of GLAD and GLFW. GLAD needs to be included before GLFW, otherwise you get the error `fatal error C1189: #error:  OpenGL header already included, remove this include, glad already provides it`.

``````cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
``````

In the main function, initialize GLFW and provide some information on features of our window.

```cpp
glfwInit();  // must be called before calling most GLFW functions - initializes GLFW.
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // sets '3' as the Major version hint for when glfwCreateWindow is called
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // sets '3' as the Minor version hint for when glfwCreateWindow is called
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // explicitly use core-profile functions (glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE) for Mac OS X)
```

Now we can create the window. Note that `glfwCreateWindow` returns a pointer.

```cpp
GLFWwindow* window = glfwCreateWindow(800, 600, "Window name", NULL, NULL);  // create the window
if (window == NULL) {  // if the window is NULL, an error has occurred
    std::cout << "Failed to create GLFW window\n";
    glfwTerminate();  // terminate GLFW upon error
    return -1;
}
glfwMakeContextCurrent(window);  // activate the window (makes the OpenGL or OpenGL ES context of the specified window)
```

GLFW has passed all the checks. Now we do the same for GLAD

```cpp
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD\n";
    return -1;
}
```

We need to define the dimensions of the window where OpenGL can draw. This is known as the *viewport*. Typically, the viewport covers the whole window. We can call it once at the start, but that will only update the viewport then. The viewport will not change if we were to later resize the window. By creating a function with `glViewport`, we can update the viewport the moment a user resizes the window.

```cpp
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);  // sets OpenGL's boundaries in the window
}

int main() {
    /* previous code */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  // calls our viewport function whenever the window is resized
}
```

Now we can create the *render loop*. This loop will allow us to continuously draw images to the screen, rather than drawing the initial frame then exiting. 

```cpp
while (!glfwWindowShouldClose(window)) {  // the render loop
    glfwSwapBuffers(window);  // double buffers fix screen tearing
    glfwPollEvents();  // handles events in the event queue
}
glfwTerminate();  // terminates GLFW after completion
return 0;
```

That is all the starter code for creating a window. All of it can be found on [learningopengl][window_code].

##### Linker Problems

Upon building the project, the linker error occurred: `unresolved external symbol _gladLoadGLLoader`. I was sure I followed the tutorial correctly, but found that adding a file to your Visual Studio project is not as simple as dragging it into the project directory. [This][glad_error] source helped me realize that you need to make `glad.c` a "project item"; in other words *right-clicking* the solution, then *adding* the new item "`glad.c`".

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