#version 330 core

out vec4 FragColor;

in vec3 Position;

uniform samplerCube Skybox;

void main()
{
    FragColor = vec4(texture(Skybox, Position).rgb, 1.0);
}