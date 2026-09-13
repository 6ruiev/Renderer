#include <iostream>
#include <stb_image.h>

#include <glad/glad.h>
#include "Window.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
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

	stbi_set_flip_vertically_on_load(true);

	float vertices[]
	{
		 // positions				// color					// texture
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f
	};

	unsigned int indices[]
	{
		0, 1, 2,
		2, 3, 0
	};


	Texture texture0(GL_TEXTURE_2D);
	texture0.TexParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	texture0.TexParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	texture0.TexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	texture0.TexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	texture0.LoadTexture("res/textures/container.jpg", 0, GL_RGB, GL_RGB);

	Texture texture1(GL_TEXTURE_2D);
	texture1.TexParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	texture1.TexParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	texture1.TexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	texture1.TexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	texture1.LoadTexture("res/textures/pirate.png", 0, GL_RGB, GL_RGBA);

	texture0.ActiveTexUnit(GL_TEXTURE0);
	texture1.ActiveTexUnit(GL_TEXTURE1);


	Shader shader("res/shaders/Basic.shader");
	shader.Bind();

	shader.SetUniform1i("texture0", 0);
	shader.SetUniform1i("texture1", 1);


	VertexBuffer VBO(vertices, sizeof(vertices), GL_STATIC_DRAW);

	VertexArray VAO;

	VAO.AttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	VAO.AttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO.AttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	IndexBuffer IBO(indices, sizeof(indices));

	VBO.Unbind();
	VAO.Unbind();
	IBO.Unbind();

	glClearColor(0.2f, 0.5f, 0.3f, 1.0f);

	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		shader.SetUniform1f("x_offset", Config::x_offset);
		shader.SetUniform1f("y_offset", Config::y_offset);
		shader.SetUniform1f("mixValue", Config::mix);

		VAO.Bind();

		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

		glfwSwapBuffers(window.GetWindow());
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}