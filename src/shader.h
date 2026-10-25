#pragma once
#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
public:
	Shader(const std::string& filePath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1f(const std::string& uniform, float v) const;
	void SetUniform1i(const std::string& uniform, int i) const;
	void SetUniformMatrix4fv(const std::string& uniform, GLsizei count, GLboolean transpose, const GLfloat* value) const;

	int GetUniformLocation(const std::string& uniform) const;

	unsigned int GetID() const;

private:
	unsigned int ID;
};


