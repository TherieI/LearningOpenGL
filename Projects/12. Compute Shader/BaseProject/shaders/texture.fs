#version 430 core
out vec4 FragColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D tex;

void main()
{
    vec3 texCol = texture(tex, TexCoord).rgb;      
    FragColor = vec4(texCol, 1.0);
}