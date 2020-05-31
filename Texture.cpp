#include "Texture.h"



Texture::Texture(const char *fileName, GLenum type)
{
	if (this->id)
	{
		glDeleteTextures(1, &this->id);
	}

	this->type = type;
	unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

	GLuint texture0;
	glGenTextures(1, &this->id);
	glBindTexture(this->type, this->id);

	glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);



	if (image)
	{
		glTexImage2D(this->type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(this->type);
	}
	else
	{
		std::cout << "ERROR:: -TEXTURE- TEXTURE LOADING FAILED IN: " << fileName << std::endl;
	}

	glActiveTexture(0);
	glBindTexture(this->type, 0);
	SOIL_free_image_data(image);
}


Texture::~Texture()
{
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

void Texture::loadFromFile(const char *fileName)
{
	if (this->id)
	{
		glDeleteTextures(1, &this->id);
	}
	unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

	GLuint texture0;
	glGenTextures(1, &this->id);
	glBindTexture(this->type, this->id);

	glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);



	if (image)
	{
		glTexImage2D(this->type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(this->type);
	}
	else
	{
		std::cout << "ERROR:: -TEXTURE-LOAD FROM FILE- TEXTURE LOADING FAILED IN: " << fileName << std::endl;
	}
	glActiveTexture(0);
	glBindTexture(this->type, 0);
	SOIL_free_image_data(image);
}