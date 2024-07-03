#version 330 core

out vec4 FragColor;


in vec2 TexCoord;
in vec3 Normal;
in vec3 crntPos;


// texture samplers
uniform sampler2D tex0;


uniform vec4 lightColor; 
uniform vec3 lightPos;

uniform vec3 camPos;

vec4 specularLighting()
{
	float ambient = 0.1f;
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diff = max(dot(normal, lightDirection), 0.0f);

	return texture(tex0, TexCoord) * (diff + ambient) * lightColor;
}

void main()
{
	FragColor = specularLighting();
}