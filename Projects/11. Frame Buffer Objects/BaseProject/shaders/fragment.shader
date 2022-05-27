#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D prevFrame;

void main()
{
    
    FragColor = vec4(color, 1.0f) + texture(prevFrame, texCoord);
}