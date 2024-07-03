#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

struct Vertex
{
    glm::vec3 Position;
    glm::vec2 TexUV;
    glm::vec3 Normal;
};

class VBO
{
public:
	GLuint ID;
	// construktor generuje ID i linkuje informacje o wierzcholkach
	VBO(std::vector<Vertex>& vertices);
	VBO(GLfloat* vertices, GLuint size);

	// bind
	void Bind();
	// unbind
	void Unbind();
	// usuwanie
	void Delete();
};

#endif