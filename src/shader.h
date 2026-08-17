#pragma once
#include <string>

class Shader
{
public:
	Shader(const std::string& filePath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	unsigned int getID() const;

private:
	unsigned int ID;
};


