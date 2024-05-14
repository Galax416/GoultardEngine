#version 330 core

layout(location = 0) in vec3 aPos;


out vec3 TexCoords;
out vec3 Normal;
out float visibility;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

const float density = 0.0005;
const float gradient = 1.5;

void main()
{
    TexCoords = (Model * vec4(aPos, 1.0)).xyz;
    gl_Position = Projection * View * vec4(TexCoords, 1.0);

    vec4 positionRelativeToCamera = View * Model * vec4(aPos, 1.0);
    float distance = length(positionRelativeToCamera.xyz);
    visibility = exp(-pow((distance*density), gradient));
    visibility = clamp(visibility, 0.0, 1.0);
}