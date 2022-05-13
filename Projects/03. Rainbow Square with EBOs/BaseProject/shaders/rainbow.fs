#version 330 core

out vec4 FragColor;
in vec3 aColor;

uniform float time;

void main()
{
    vec3 offset = vec3(0.5);
    FragColor = vec4(sin(time + aColor)/2 + offset, 1.0f);
}