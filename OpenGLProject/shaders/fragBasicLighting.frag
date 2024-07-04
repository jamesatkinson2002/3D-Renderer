#version 330 core

in vec3 outNormal;
in vec2 TexCoords;
in vec3 fragPos;

out vec4 fragColor;

uniform vec3 lightColor;

uniform vec3 viewPos; //camera's position in the world-space.

struct Light{
	//vec3 position;	//no longer necessary when using directional lights
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;

struct Material{
	sampler2D diffuse;		//diffuse map is basically the same as a texture
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

uniform Material material;

void main(){
    vec3 norm = normalize(outNormal);

	vec3 viewDir = normalize(viewPos - fragPos);

	//direction vector between the fragment and the light source positions.
	//vec3 lightDir = normalize(light.position - fragPos);

	vec3 lightDir = normalize(-light.direction);		//directional light ie. simulating a sun effect.
	
	//light direction is negated so it comes from the light source towards the fragment.
	vec3 reflectedDir = reflect(-lightDir, norm);

	//last argument is the shininess value of the specular highlight.
	float spec = pow(max(dot(viewDir, reflectedDir), 0.0), material.shininess);

	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

	vec3 emission = texture(material.emission, TexCoords).rgb;

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 result = ambient + diffuse + specular + emission;


	fragColor = vec4(result, 1.0f);
}