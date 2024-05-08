#version 330 core

// Ouput data
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse1;

// ----Phong -----
vec3 pointLightPos = vec3(0, 100, 0);
vec3 pointLightColor = vec3(1,1,1);

void main() {  

    // Get Color 
    vec3 color = texture(texture_diffuse1, TexCoords).rgb;

    // Ambient lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * color;

    // Diffuse lighting
    vec3 lightDir = normalize(pointLightPos - FragPos);
    vec3 normal = normalize(Normal);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * pointLightColor * color;

    // Specular lighting
    float specularStrength = 0.3;
    vec3 viewDir = normalize(- FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);    
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * pointLightColor;

    // Final color
    vec3 result = (ambient + diffuse + specular);

    FragColor = vec4(result, 1.0);


    FragColor = texture(texture_diffuse1, TexCoords);
}