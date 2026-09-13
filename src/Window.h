#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include "Config.h"

class Window 
{
public:
	~Window();

	void DestroyWindow();
	
	void GLFWInit();
	GLFWwindow* InitWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	GLFWwindow* GetWindow() const;

	void SetViewPortSize(GLint x, GLint y, GLsizei width, GLsizei height);
	void SetViewPortSize();
	void SetCallbacks();

	Window& operator=(Window&& other);

private:
	GLFWwindow* window_ = nullptr;
};

