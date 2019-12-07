#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aNormal;

uniform vec3 viewer;
uniform vec3 lightPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;




out vec3 lighting;
out vec3 Normal;

void main()
{


	
    vec3 lightColor = vec3(1,1,1);
    gl_Position = projection * view * model * vec4(position, 1.0);

    float ambientStrength = 0.4;
    vec3 ambient = ambientStrength * lightColor;



    vec3 Position = vec3(model * vec4(position,1.0));

    vec3 Normal = aNormal;



    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - Position);
    float diff = max(dot(norm,lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 1.0f;
    vec3 viewDir = normalize(viewer - Position);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
    vec3 specular = specularStrength * spec * lightColor;

    lighting = ambient;

}

