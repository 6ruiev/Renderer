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


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


int main()
{
	stbi_set_flip_vertically_on_load(true);


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

	float vertices[] = {
		 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		  0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		 -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		  0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		  0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[]{
		 glm::vec3(0.0f,  0.0f,  0.0f),
		 glm::vec3(2.0f,  5.0f, -15.0f),
		 glm::vec3(-1.5f, -2.2f, -2.5f),
		 glm::vec3(-3.8f, -2.0f, -12.3f),
		 glm::vec3(3.0f, -0.4f, -3.5f),
		 glm::vec3(-1.7f,  3.0f, -7.5f),
		 glm::vec3(1.3f, -2.0f, -2.5f),
		 glm::vec3(1.5f,  2.0f, -2.5f),
		 glm::vec3(1.5f,  0.2f, -1.5f),
		 glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	unsigned int indices[]
	{
		0, 1, 2,
		2, 3, 0
	};

	/////////

	Texture texture0(GL_TEXTURE_2D);
	texture0.TexParameteri(GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	texture0.TexParameteri(GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	texture0.TexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	texture0.TexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	texture0.LoadTexture("res/textures/cobblestone.png", 0, GL_RGB, GL_RGBA);

	Texture texture1(GL_TEXTURE_2D);
	texture1.TexParameteri(GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	texture1.TexParameteri(GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	texture1.TexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	texture1.TexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	texture1.LoadTexture("res/textures/container.jpg", 0, GL_RGB, GL_RGBA);

	texture0.TexUnit(GL_TEXTURE0);
	texture1.TexUnit(GL_TEXTURE1);

	Shader shader("res/shaders/Basic.shader");
	shader.Bind();

	shader.SetUniform1i("texture0", 0);
	shader.SetUniform1i("texture1", 1);

	/////////

	VertexBuffer VBO(vertices, sizeof(vertices), GL_STATIC_DRAW);
	VertexArray VAO;

	VAO.AttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	//VAO.AttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO.AttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	IndexBuffer IBO(indices, sizeof(indices));

	VBO.Unbind();
	VAO.Unbind();
	IBO.Unbind();

	/////////

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, -1.0f, -6.0f));
	shader.SetUniformMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(view));

	/////////

	glClearColor(83.0f / 255.0f, 88.0f / 255.0f, 84.0f / 255.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.SetUniform1f("x_offset", Config::x_offset);
		shader.SetUniform1f("y_offset", Config::y_offset);
		shader.SetUniform1f("mixValue", Config::mix);

		VAO.Bind();

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(60.0f), Config::width / Config::height, 0.1f, 100.0f);
		shader.SetUniformMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(projection));

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, glm::radians(Config::rotate), glm::vec3(1.0f, 1.0f, 0.0f));
			shader.SetUniformMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(model));
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		}

		glfwSwapBuffers(window.GetWindow());
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}



