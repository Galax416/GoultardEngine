#version 330 core

// Input vertex data, different for all executions of this shader.
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

// Output data ; will be interpolated for each fragment.
out vec2 TexCoords;


uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main(){

        TexCoords = aTexCoords; 

        mat4 MVP = Projection * View * Model;

        // TODO : Output position of the vertex, in clip space : MVP * position
        gl_Position = MVP * vec4(aPos,1);

}

