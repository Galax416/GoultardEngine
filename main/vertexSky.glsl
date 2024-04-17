#version 330 core

layout(location = 0) in vec3 vertices_position_modelspace;

out vec3 Position;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
    Position = vec3(Model * vec4(vertices_position_modelspace, 1.0));
    gl_Position = Projection * View * vec4(Position, 1.0);
}