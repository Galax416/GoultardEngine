#version 330 core

// Ouput data
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse1;

// ----Phong -----
uniform vec3 pointLightPos;
vec3 pointLightColor = vec3(1,1,1);

void main() {  

    // Get Color 
    vec3 color = texture(texture_diffuse1, TexCoords).rgb;

    // Ambient lighting
    float ambientStrength = 0.8;
    vec3 ambient = ambientStrength * color;

    // Diffuse lighting
    vec3 lightDir = normalize(pointLightPos - FragPos);
    vec3 normal = normalize(Normal);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * pointLightColor * color;

    // Specular lighting
    float specularStrength = 0.1;
    vec3 viewDir = normalize(- FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);    
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * pointLightColor;

    // spotlight (soft edges)
    // float theta = dot(lightDir, normalize(-vec3(0, -1, 0))); 
    // float epsilon = (cos(radians(52.5)) - cos(radians(57.5)));
    // float intensity = clamp((theta - cos(radians(57.5))) / epsilon, 0.0, 1.0);
    // diffuse  *= intensity;
    // specular *= intensity;


    // attenuation
    float distance    = length(pointLightPos - FragPos);
    float attenuation = 1.0 / (1.0 + 0.00009 * distance + 0.000032 * (distance * distance));    
    ambient  *= attenuation; 
    diffuse  *= attenuation;
    specular *= attenuation;  

    // Final color
    vec3 result = (ambient + diffuse + specular);

    FragColor = vec4(result, 1.0);


    FragColor = texture(texture_diffuse1, TexCoords);
}