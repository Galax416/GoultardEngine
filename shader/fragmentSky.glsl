#version 330 core

out vec4 FragColor;

in vec3 TexCoords;
in float visibility;

uniform samplerCube Skybox;
uniform bool isEditMode;

void main()
{
    FragColor = vec4(texture(Skybox, TexCoords).rgb, 1.0);

    if (!isEditMode) FragColor = mix(vec4(0.62, 0.70, 0.75, 1.0), FragColor, visibility);
}