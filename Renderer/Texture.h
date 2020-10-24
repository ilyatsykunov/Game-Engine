#pragma once
#include <iostream>
#include <string>
#include <GLEW\glew.h>
#include <GLFW\glfw3.h>
#include <SOIL2\SOIL2.h>

class Texture
{
private:
	GLuint id;
	int width;
	int height;
	GLuint type;
	const GLchar* fileName;
	const std::string typeName;
	const std::string path;

public:
	Texture(const GLchar* fileName, const GLchar* path, const std::string typeName);
	~Texture();
	inline const GLuint getID() { return this->id; }
	const GLchar* getName() const { return this->fileName; }
	const std::string getTypeName() const { return this->typeName; }
	inline const GLuint getType() { return this->type; }
	inline std::string getPath() { return this->path; }


	void bind(const GLint);
	void unbind();
};

