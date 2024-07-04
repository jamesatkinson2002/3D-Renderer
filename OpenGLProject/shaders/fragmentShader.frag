#version 330 core

in vec2 outTexCoords;

out vec4 fragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixValue;

void main(){
	fragColor = mix(texture(texture1,outTexCoords), texture(texture2, vec2(outTexCoords.x, outTexCoords.y)), mixValue);
}