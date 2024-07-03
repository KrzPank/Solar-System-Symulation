#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;


out vec2 TexCoord;
out vec3 Normal;
out vec3 crntPos;


uniform mat4 model;
uniform mat4 projView;
uniform mat4 scale;
uniform mat4 translation;
uniform mat4 spin; 


void main()
{
	mat4 result = translation  * model * spin * scale;
	crntPos = vec3(result * vec4(aPos, 1.0f));

	gl_Position = projView *  vec4(crntPos, 1.0f);

	TexCoord = vec2(aTexCoord.x, aTexCoord.y);

	Normal = mat3(transpose(inverse(result))) * aNormal;
}