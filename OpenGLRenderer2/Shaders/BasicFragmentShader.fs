#version 440
out vec4 FragColor;

in vec2 texCoords;

void main()
{
    vec3 colour = vec3(1.f,1.f,1.f);
    vec3 ambientColour = vec3(0.2f, 0.2f, 0.28f);
    colour = colour * ambientColour;

    FragColor = vec4(colour, 1.0f);
} 