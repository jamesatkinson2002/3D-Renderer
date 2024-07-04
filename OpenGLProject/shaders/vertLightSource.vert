#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 outNormal;
out vec3 fragPos;
out vec2 TexCoords; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	TexCoords = texCoords;
	
	//if the model was non-uniformly scaled, the normal vector would change direction (as the magnitude is affected) and the lighting would be distorted.
	//the normal matrix ie. the transpose of the inverse of the upper left 3x3 part of the model matrix (wtf??).
	//converting it to a mat3 means it will lose it's translation properties.
	//inversing a matrix is an expensive operation so ideally, the normal matrix should be passed in as a uniform variable.
    outNormal = mat3(transpose(inverse(model))) * normal;
	
	fragPos = vec3(model * vec4(pos, 1.0));
	
	//multiplication from right to left
	gl_Position = projection * view * model * vec4(pos.x, pos.y, pos.z, 1.0);
}