#version 330 core


out vec4 FragColor;

in vec3 lightingColor;
in vec3 inPos;
in vec3 inNorm;


uniform vec3 color;
uniform vec3 lightPos;
uniform vec3 viewPos;


void main(){
	vec3 lightColor = vec3(1,1,1);
	//vec3 viewPos = vec3(0,0,3);

	float dir = length(inPos - lightPos);
	float ambientStrength = 0.7;
	vec3 ambient = ambientStrength * lightColor;
	
	//diffuse not working
	vec3 n = normalize(inNorm);
	vec3 lightDir = normalize(lightPos - inPos);
	float diff = max(dot(n,lightDir),0.0);
	vec3 diffuse = diff*lightColor;

	float specStrength = 0.5;
	vec3 viewDir = normalize(viewPos - inPos);
	vec3 reflectDir = reflect(-lightDir, n);
	float spec = pow(max(dot(viewDir, reflectDir),0.0),32);
	vec3 specular = specStrength*spec*lightColor;


	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result*color,1.0);

}