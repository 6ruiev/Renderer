#include "OpenGL.h"
#include "Window.h"
#include <iostream>
#include <stb_image.h>

#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Debug.h"
#include "Config.h"


int main()
{
	Window window;

	window.GLFWInit();
	window.InitWindow(800, 600, "OpenGL", 0, 0);
	window.SetViewPortSize();
	window.SetCallbacks();

	// GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	float vertices[]
	{
		 // positions				// color					// texture
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		-1.0f, -1.0f,
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,		 1.0f, -1.0f,
		 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 0.0f,		 1.0f,  1.0f,
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 1.0f,		-1.0f,  1.0f
	};

	unsigned int indices[]
	{
		0, 1, 2,
		2, 3, 0
	};

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int textureWidth, textureHeight, nrChannels;
	unsigned char* data = stbi_load("res/textures/wall.jpg", &textureWidth, &textureHeight, &nrChannels, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	Shader shader("res/shaders/Basic.shader");
	shader.Bind();

	VertexBuffer VBO(vertices, sizeof(vertices));

	VertexArray VAO;

	VAO.AttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	VAO.AttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO.AttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO.EnableAttribArray(0);
	VAO.EnableAttribArray(1);
	VAO.EnableAttribArray(2);

	IndexBuffer IBO(indices, sizeof(indices));

	VBO.Unbind();
	glBindVertexArray(0);
	IBO.Unbind();

	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		glClearColor(0.4f, 0.6f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.SetUniform1f("x_offset", Offset::x_offset);
		shader.SetUniform1f("y_offset", Offset::y_offset);

		VAO.Bind();

		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

		glfwSwapBuffers(window.GetWindow());
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}