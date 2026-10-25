#pragma once
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>


class Texture
{
public:

	Texture(GLenum target);

	void Bind() const;
	void Unbind() const;

	void TexParameteri(GLenum pname, GLint param) const;
	void LoadTexture(const char* texture, GLint level, GLint internalFormat, GLenum format) const;
	void TexUnit(GLenum textureUnit) const;

private:
	unsigned int ID;
	GLenum target_;
};