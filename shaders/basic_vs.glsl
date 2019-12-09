//with help from Learnopengl.com
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

//out vec3 lightingColor;
out vec3 inPos;
out vec3 inNorm;

//uniform vec3 viewPos;



uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	inPos = vec3(model*vec4(aPos,1.0));
	inNorm = normalize(mat3(model)*aNormal);
	gl_Position = projection * view * model * vec4(aPos,1.f);
}