#pragma once
#include <GLFW/glfw3.h>

class Window 
{
public:
	~Window();

	void DestroyWindow();
	void operator=(Window& window);
	
	void GLFWInit();
	GLFWwindow* InitWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	GLFWwindow* GetWindow();

	void SetViewPortSize(GLint x, GLint y, GLsizei width, GLsizei height);
	void SetViewPortSize();
	void SetCallbacks();

private:
	GLFWwindow* window_ = nullptr;
};

