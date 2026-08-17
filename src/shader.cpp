#include "OpenGL.h"
#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>


namespace  
{
	struct ShaderProgramSource
	{
		std::string vertexSource;
		std::string fragmentSource;
	};

	ShaderProgramSource ParseShader(const std::string& filePath)
	{
		enum class ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		std::stringstream ss[2];
		std::ifstream stream(filePath);

		ShaderType type = ShaderType::NONE;
		std::string line;

		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else if (type != ShaderType::NONE)
			{
				ss[(int)type] << line << '\n';
			}
		}

		return { ss[0].str(), ss[1].str() };
	}

	bool ProgramLinkStatus(unsigned int program)
	{
		int succes;

		glGetProgramiv(program, GL_LINK_STATUS, &succes);

		if (succes)
		{
			return true;
		}

		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* message = static_cast<char*>(alloca(length));

		glGetProgramInfoLog(program, length, &length, message);

		std::cout << " :::::: PROGRAM LINKING ERROR :::::: \n" << message << std::endl;

		return false;
	}

	bool ShaderCompileStatus(unsigned int type, unsigned int shader)
	{
		int success;

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (success)
			return true;

		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* message = static_cast<char*>(alloca(length));

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
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	unsigned int CreateShader(const ShaderProgramSource& source)
	{
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, source.vertexSource);

		if (vs == 0)
		{
			return 0;
		}

		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, source.fragmentSource);

		if (fs == 0)
		{
			glDeleteShader(vs);
			return 0;
		}

		unsigned int program = glCreateProgram();

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		if (!ProgramLinkStatus(program))
		{
			glDeleteProgram(program);
			return 0;
		}

		return program;
	}

}


Shader::Shader(const std::string& filePath)
{
	ShaderProgramSource source = ParseShader(filePath);
	ID = CreateShader(source);
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

void Shader::Bind() const
{
	glUseProgram(ID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

unsigned int Shader::getID() const
{
	return ID;
}



