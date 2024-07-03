#include "VAO.h"

// generuje ID
VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

// linkuje atrybuty do VAO
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
    VBO.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

// bind
void VAO::Bind()
{
    glBindVertexArray(ID);
}

// unbind
void VAO::Unbind()
{
    glBindVertexArray(0);
}

// usuwanie
void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}