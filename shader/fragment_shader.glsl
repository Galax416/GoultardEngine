#version 330 core

// Ouput data
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in float visibility;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;

uniform samplerCube Skybox;

uniform bool isEditMode;

// ----Phong -----
uniform vec3 pointLightPos;
vec3 lightDirection = (vec3(1, -1, 0)); // directional light 
uniform vec3 cameraPos;


void main() {  

    
    // Get Color 
    vec3 color = texture(texture_diffuse1, TexCoords).rgb;

    // Get Normal
    vec3 normal = texture(texture_normal1, TexCoords).rgb;

    normal = normalize(normal * 2.0 - 1.0); // transform normal vector to range [-1,1]
    
    
    // Ambient lighting
    vec3 ambient = 0.4 * color;

    // Diffuse lighting
    // vec3 lightDir = normalize(pointLightPos - FragPos);
    vec3 lightDir = normalize(lightDirection);  
    // vec3 normal = normalize(Normal);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * color;

    // Specular lighting
    vec3 viewDir = normalize(- FragPos);
    vec3 reflectDir = reflect(-lightDir, normal); // Phong
    vec3 halfwayDir = normalize(lightDir + viewDir); // Blin Phong
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = 0.5 * spec * vec3(1.0);


    // attenuation
    float distance = length(pointLightPos - FragPos);
    float attenuation = 1.0 / (1.0 + 0.00009 * distance + 0.000032 * (distance * distance));    
 
    // Final color
    vec3 result = (ambient + diffuse + specular) ;//* attenuation;

    FragColor = vec4(result, 1.0);
    if (!isEditMode) FragColor = mix(vec4(0.62, 0.70, 0.75, 1.0), FragColor, visibility);

    

    // FragColor = texture(texture_diffuse1, TexCoords);
}