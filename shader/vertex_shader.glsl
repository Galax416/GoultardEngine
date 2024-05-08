#version 330 core

// Input vertex data, different for all executions of this shader.
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

// Output data ; will be interpolated for each fragment.
out vec2 TexCoords;
out vec3 FragPos; // Position of the fragment in world space
out vec3 Normal; // Normal of the fragment in world space

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main(){
        
        // UVs texture
        TexCoords = aTexCoords; 

        // Position world
        FragPos = (Model * vec4(aPos, 1.0)).xyz; 

        // Normal world
        Normal = aNormal;//mat3(transpose(inverse(Model))) * aNormal; // Transform normal to world space

        mat4 MVP = Projection * View * Model;
        gl_Position = MVP * vec4(aPos,1);

}

