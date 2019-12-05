#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;
uniform vec3 viewPos;

out vec3 lightColor;

void main()
{
    //vec3 lightColor = vec3(1,1,1);
    gl_Position = projection * view * model * vec4(position, 1.0);
/*
    vec3 Position vec3(model * vec4(position,1.0));
    vec3 Normal = mat3(transpose(inverse(model))) * normal;

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - Position);
    float diff = max(dot(norm,lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 1.0f;
    vec3 viewDir = normalize(viewPos - Position);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
    vec3 specular = specularStrength * spec * lightColor;
*/
    lightColor = vec3(1,0,0);
    //lightColor = ambient+diffuse+specular;





}

