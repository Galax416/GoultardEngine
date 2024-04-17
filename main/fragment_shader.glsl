#version 330 core

// Ouput data
out vec4 FragColor;

uniform vec3 colorSampler;

void main(){

        FragColor = vec4(colorSampler, 1.0);//vec3(0.2, 0.2,0.4);

}
