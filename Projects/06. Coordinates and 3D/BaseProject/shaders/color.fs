#version 330 core

out vec4 FragColor;
in vec3 color;
in vec2 textureCoord;

uniform sampler2D chad;

void main()
{
    FragColor = texture(chad, textureCoord);
}