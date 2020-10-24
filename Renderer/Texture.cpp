#include "Texture.h"


Texture::Texture(const GLchar* fileName, const GLchar* path, const std::string typeName)
	: fileName(fileName), path(path), typeName(typeName)
{

	this->type = GL_TEXTURE_2D;

	if (this->id)
	{
		glDeleteTextures(1, &this->id);
	}

	int componentNum;
	unsigned char* image = SOIL_load_image(path, &this->width, &this->height, &componentNum, 0);

	if (image)
	{
		GLenum format;
		switch (componentNum)
		{
		case 1:
			format = GL_RED;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		}

		glGenTextures(1, &this->id);
		glBindTexture(this->type, this->id);
		glTexImage2D(this->type, 0, format, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(this->type);

		glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "ERROR:: -TEXTURE- TEXTURE LOADING FAILED IN: " << path << std::endl;
	}

	glActiveTexture(0);
	glBindTexture(this->type, 0);
	SOIL_free_image_data(image);
}


Texture::~Texture()
{
	free((GLchar*)this->fileName);
	glDeleteTextures(1, &this->id);
}

void Texture::bind(const GLint texture_unit)
{
	glActiveTexture(GL_TEXTURE0 + texture_unit);
	glBindTexture(this->type, this->id);
}

void Texture::unbind()
{
	glActiveTexture(0);
	glBindTexture(this->type, 0);
}