#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D chadTexture;

void main()
{
    FragColor = texture(chadTexture, TexCoord);
}