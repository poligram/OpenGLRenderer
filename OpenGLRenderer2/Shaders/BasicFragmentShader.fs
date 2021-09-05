#version 440
out vec4 FragColor;

in vec2 texCoords;

void main()
{
    vec3 colour = vec3(1.f,1.f,1.f);
    colour = colour * vec3(texCoords, 0.f);

    FragColor = vec4(colour, 1.0f);
} 