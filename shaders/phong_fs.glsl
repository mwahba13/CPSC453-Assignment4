#version 330 core
out vec4 fragColor;

in vec3 lighting;
in vec3 Normal;



void main()
{

    vec3 objectColor = vec3(0.3,1,0);

    fragColor = vec4(lighting*objectColor, 1.0);

}
