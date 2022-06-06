# Frame Buffer Objects

In this project, I attempted to learn what *Frame Buffer Objects* (FBOs) are and how to use them.



### What are FBOs?

Drawing anything to the screen requires the use of a Frame Buffer. Thankfully, OpenGL creates one for us! Up until now we've been using OpenGL's default FBO to satisfy our graphical desires, but there are certain effects that can only be done with other framebuffers. These ...



### Creating a Frame Buffer Object

Along the way, I forgot to specify my the directories of my shaders (something like this `Shader framebufferShader = Shader("shader/", "shader/");`) which resulted in the following interesting output.

<img src="Documentation\1. Shader Error.gif" alt="1. Shader Error" style="zoom:100%;" />



