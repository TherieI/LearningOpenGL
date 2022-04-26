#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform float height;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec3 pos = aPos;
    if (aPos.y > 0.0f) {
        pos = vec3(aPos.x, aPos.y * height, aPos.z);
    }
    gl_Position = projection * view * model * vec4(pos, 1.0);
    color = aColor;
}