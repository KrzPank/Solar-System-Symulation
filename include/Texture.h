#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h> 
#include<stb/stb_image.h>

#include "Shader.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	GLuint unit;

	// konstruktor z wczytaniem textury
    Texture(const char* image, GLuint slot, GLenum format, GLenum texType = GL_TEXTURE_2D, GLenum pixelType = GL_UNSIGNED_BYTE);
	Texture();

	// przypisuje texture do shadera
	void texUnit(Shader& shader, const char* uniform, GLuint unit);

	// bind
	void Bind();

	// unbind
	void Unbind();


	void operator=(Texture& texture);

	// usuwanie
	void Delete();
};

#endif
