#include "Window.h"
#include <iostream>
#include "Config.h"

namespace Callbacks
{
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action != GLFW_PRESS && action != GLFW_REPEAT)
		{
			return;
		}

		if (key == GLFW_KEY_W)
		{
			Offset::y_offset += 0.01f;
		}

		if (key == GLFW_KEY_S)
		{
			Offset::y_offset -= 0.01f;
		}

		if (key == GLFW_KEY_D)
		{
			Offset::x_offset += 0.01f;
		}

		if (key == GLFW_KEY_A)
		{
			Offset::x_offset -= 0.01f;
		}

		if (key == GLFW_KEY_ESCAPE)
		{
			glfwSetWindowShouldClose(window, true);
		}

		if (key == GLFW_KEY_F1)
		{
			glfwMaximizeWindow(window);
		}

		if (key == GLFW_KEY_F2)
		{
			glfwRestoreWindow(window);
		}
	}
}

Window::~Window()
{
	glfwDestroyWindow(window_);
}

void Window::DestroyWindow()
{
	glfwDestroyWindow(window_);
	window_ = nullptr;
}

void Window::operator=(Window& w)
{
	if (window_)
	{
		DestroyWindow();
	}

	window_ = w.GetWindow();

	w.window_ = nullptr;
	w.DestroyWindow();
}

void Window::GLFWInit()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
}

GLFWwindow* Window::InitWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	if (window_)
	{
		DestroyWindow();
	}

	window_ = glfwCreateWindow(width, height, title, monitor, share);

	if (window_ == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window_);

	return window_;
}

GLFWwindow* Window::GetWindow()
{
	return window_;
}

void Window::SetViewPortSize(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glViewport(x, y, width, height);
}

void Window::SetViewPortSize()
{
	int width, height;

	glfwGetFramebufferSize(window_, &width, &height);
	glViewport(0, 0, width, height);
}

void Window::SetCallbacks()
{
	glfwSetFramebufferSizeCallback(window_, Callbacks::framebuffer_size_callback);
	glfwSetKeyCallback(window_, Callbacks::key_callback);
}