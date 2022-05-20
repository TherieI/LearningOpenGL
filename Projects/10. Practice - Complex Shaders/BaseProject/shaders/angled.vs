#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 aColor;
uniform mat4 u_mvp;

void main()
{
    gl_Position = u_mvp * vec4(aPos, 1.0);
    aColor = vec3(0.5f, 0.5f, 0.5f);
}