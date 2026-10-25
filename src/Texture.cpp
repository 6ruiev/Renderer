#include "Texture.h"


Texture::Texture(GLenum target)
{
	glGenTextures(1, &ID);
	glBindTexture(target, ID);

	target_ = target;
}

void Texture::Bind() const
{
	glBindTexture(target_, ID);
}

void Texture::Unbind() const
{
	glBindTexture(target_, 0);
}

void Texture::TexParameteri(GLenum pname, GLint param) const
{
	glTexParameteri(target_, pname, param);
}

void Texture::LoadTexture(const char* texture, GLint level, GLint internalFormat, GLenum format) const
{
	int textureWidth, textureHeight, nrChannels;
	unsigned char* data = stbi_load(texture, &textureWidth, &textureHeight, &nrChannels, STBI_rgb_alpha);

	if (data)
	{
		switch (target_)
		{
		case GL_TEXTURE_2D:
			glTexImage2D(GL_TEXTURE_2D, level, internalFormat, textureWidth, textureHeight, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			break;
			
		// ------------------------------------------------------------------------------------------------------------


		default:
			break;
		}
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
}


void Texture::TexUnit(GLenum textureUnit) const
{
	glActiveTexture(textureUnit);
	this->Bind();
}
