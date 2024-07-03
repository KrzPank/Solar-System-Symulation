#include "VBO.h"

// tworzy VBO i linkuje informacje o wierzcholkach
VBO::VBO(std::vector<Vertex>& vertices)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

// tworzy VBO i linkuje informacje o wierzcholkach
VBO::VBO(GLfloat* vertices, GLuint size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// bind
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

//unbind VBO
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// usuwa VBO
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}