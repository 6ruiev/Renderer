#pragma once
#include <glad/glad.h>

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size, GLenum usage);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int ID;
};