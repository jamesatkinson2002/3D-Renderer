#version 330 core

out vec4 fragColor;

uniform vec3 lightSourceColor;

void main(){
	fragColor = vec4(lightSourceColor, 1.0f);
}