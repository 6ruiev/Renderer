#pragma once
#include <string>

class Shader
{
public:
	Shader(const std::string& filePath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1f(const std::string& uniform, float v) const;
	int GetUniformLocation(const std::string& uniform) const;

	unsigned int GetID() const;

private:
	unsigned int ID;
};


