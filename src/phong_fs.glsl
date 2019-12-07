#version 330 core
out vec4 fragColor;

in vec3 lightColor;


void main()
{
    vec3 objectColor = vec3(0.3,1,0);
    fragColor = vec4(lightColor*objectColor, 1.0);
}
