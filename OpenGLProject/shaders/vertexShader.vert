#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	TexCoords = texCoords;

	//multiplication from right to left
	gl_Position = projection * view * model * vec4(pos.x, pos.y, pos.z, 1.0);
}