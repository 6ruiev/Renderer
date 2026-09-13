#pragma once
#include <glad/glad.h>
#include <iostream>

namespace Debug 
{
	void GLClearError();

	bool GLCheckError(const char* file, const char* function, int line);
}


#define ASSERT(x) if (!(x)) __debugbreak();

#define GLCall(x) Debug::GLClearError();\
	x;\
	ASSERT(Debug::GLCheckError(__FILE__, #x, __LINE__))