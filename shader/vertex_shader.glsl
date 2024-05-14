#version 330 core

// Input vertex data, different for all executions of this shader.
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;


// Output data ; will be interpolated for each fragment.
out vec2 TexCoords;
out vec3 FragPos; // Position of the fragment in world space
out vec3 Normal; // Normal of the fragment in world space
out float visibility;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

const float density = 0.0007;
const float gradient = 1.5;

void main(){
        
        // UVs texture
        TexCoords = aTexCoords; 

        // Position world
        FragPos = (Model * vec4(aPos, 1.0)).xyz; 

        // Normal world
        Normal = mat3(transpose(inverse(Model))) * aNormal; 

        vec4 positionRelativeToCamera = View * Model * vec4(aPos, 1.0);
        float distance = length(positionRelativeToCamera.xyz);
        visibility = exp(-pow((distance*density), gradient));
        visibility = clamp(visibility, 0.0, 1.0);

        mat4 MVP = Projection * View * Model;
        gl_Position = MVP * vec4(aPos,1);

}

