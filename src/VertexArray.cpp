#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &ID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(ID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::AttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer) const
{
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void VertexArray::EnableAttribArray(GLuint index) const
{
	glEnableVertexAttribArray(index);
}

unsigned int VertexArray::GetID() const
{
	return ID;
}