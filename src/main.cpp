#include "OpenGL.h"
#include "Window.h"
#include <iostream>

#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Debug.h"


static float x_offset = 0.0f;
static float y_offset = 0.0f;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS)
	{
		return;
	}

	if (key == GLFW_KEY_W)
	{
		y_offset += 0.01f;
	}

	if (key == GLFW_KEY_S)
	{
		y_offset -= 0.01f;
	}

	if (key == GLFW_KEY_D)
	{
		x_offset += 0.01f;
	}

	if (key == GLFW_KEY_A)
	{
		x_offset -= 0.01f;
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


int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);


	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", 0, 0);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);


	// GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	int width, height;

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	// Callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);


	float vertices[]
	{
		// positions    
		-0.5f,   -0.5f,   0.0f,
		 0.5f,   -0.5f,   0.0f,
		 0.5f,    0.5f,   0.0f,
		-0.5f,    0.5f,   0.0f
	};

	unsigned int indices[]
	{
		0, 1, 2,
		2, 3, 0
	};


	float texture[]
	{
		-0.5f,   -0.5f,
		 0.5f,   -0.5f,
		 0.5f,    0.5f,
		-0.5f,    0.5f
	};


	Shader shader("res/shaders/Basic.shader");
	shader.Bind();

	VertexBuffer VBO(vertices, sizeof(vertices));

	VertexArray VAO;

	VAO.AttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	VAO.EnableAttribArray(0);

	IndexBuffer IBO(indices, sizeof(indices));

	VBO.Unbind();
	glBindVertexArray(0);
	IBO.Unbind();

	unsigned int x_offsetLocation = glGetUniformLocation(shader.GetID(), "x_offset");
	unsigned int y_offsetLocation = glGetUniformLocation(shader.GetID(), "y_offset");

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.4f, 0.6f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUniform1f(x_offsetLocation, x_offset);
		glUniform1f(y_offsetLocation, y_offset);

		VAO.Bind();

		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}