#pragma once
#include <glad/glad.h>

class VertexArray
{
public:
	VertexArray();

	~VertexArray();

	void Bind() const;

	void Unbind() const;

	void AttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer) const;

	void EnableAttribArray(GLuint index) const;

	unsigned int GetID() const;

private:
	unsigned int ID;
};