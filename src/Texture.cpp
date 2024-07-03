#include "Texture.h"

// konstruktor podstawowy
Texture::Texture() {}

// operator przypisania
void Texture::operator=(Texture&texture)
{
	ID = texture.ID;
	type = texture.type;
	unit = texture.unit;
}


// konstruktor z wczytaniem textury
Texture::Texture(const char* image, GLuint slot, GLenum format, GLenum texType, GLenum pixelType)
{
    type = texType;
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);
/*
	if (bytes)
	{
		std::cout << "Loaded texture: " << image << " (" << widthImg << "x" << heightImg << ", " << numColCh << " channels)" << std::endl;
	} 
	else
	{
		std::cout << "Failed to load texture " << image << " (" << widthImg << "x" << heightImg << ", " << numColCh << " channels)" << std::endl;; 
	}
*/
	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0 + slot); 
	unit = slot;
	glBindTexture(texType, ID);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(texType, 0, GL_RGBA,	widthImg, heightImg, 0, format, pixelType, bytes);

	
	glGenerateMipmap(texType);

	stbi_image_free(bytes);

	glBindTexture(texType, 0);
}

// przypisuje texture do shadera
void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	shader.activate();
	shader.setInt(uniform, unit);
}

// aktywuje i binduje texture
void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(type, ID);
}

// unbind
void Texture::Unbind()
{
	glBindTexture(type, 0);
}

// usuwa texture
void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}