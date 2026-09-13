#include "Debug.h"

bool Debug::GLCheckError(const char* file, const char* function, int line)
{
	GLenum error = glGetError();

	if (error)
	{
		std::cout << " :::::: OPENGL ERROR :::::: \n\t"
			<< " [ " << std::hex << error << std::dec << " ]\n\n"
			<< "File: " << file << "\n"
			<< "Function: " << function << "\n"
			<< "Line: " << line
			<< std::endl;

		return false;
	}

	return true;
}

void Debug::GLClearError()
{
	while (glGetError());
}