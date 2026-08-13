#pragma once
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct ShaderSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

ShaderSource ParseShader(const std::string& filePath)
{
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::stringstream ss[2];
	std::ifstream stream(filePath);

	std::string line;
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if(line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		} 
		else if (type != ShaderType::NONE)
		{
			ss[(int)type] << line << '\n';
		}
	}

	return ShaderSource{ ss[0].str(), ss[1].str() };
}

bool ProgramLinkingStatus(unsigned int program)
{
	int succes;

	glGetProgramiv(program, GL_LINK_STATUS, &succes);

	if (succes)
		return true;

	int length;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
	char* message = (char*)(alloca(length));

	glGetProgramInfoLog(program, length, &length, message);

	std::cout << " :::::: PROGRAM LINKING ERROR :::::: " << message << std::endl;

	return false;
}

bool ShaderCompileStatus(unsigned int type, unsigned int shader) 
{
	int succes;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);

	if (succes)
		return true;

	int length;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
	char* message = (char*)(alloca(length));

	glGetShaderInfoLog(shader, length, &length, message);

	std::cout << " :::::: SHADER COMPILATION ERROR :::::: " << (type == GL_VERTEX_SHADER ? "VERTEX SHADER" : "FRAGMENT SHADER\n") << message << std::endl;

	return false;
}

unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();

	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	if (!ShaderCompileStatus(type, id))
	{
		return 0;
	}

	return id;
}

unsigned int CreateProgram(const std::string vertexShader, const std::string fragmentShader)
{
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);

	if (vs == 0)
	{
		glDeleteShader(vs);
		return 0;
	}

	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	if (fs == 0)
	{
		glDeleteShader(vs);
		glDeleteShader(fs);
		return 0;
	}

	unsigned int program = glCreateProgram();

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	if (!ProgramLinkingStatus(program))
	{
		glDeleteProgram(program);
		return 0;
	}

	return program;
}