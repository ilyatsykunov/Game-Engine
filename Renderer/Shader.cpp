#include "Shader.h"

/*
	Class for loading and updating Vertext and Fragment shaders.
*/

std::string Shader::loadShaderSource(char* fileName)
{
	std::string temp = "";
	std::string src = "";

	std::fstream in_file;

	// VERTEX SHADER
	in_file.open(fileName);

	if (in_file.is_open())
	{
		while (std::getline(in_file, temp))
			src += temp + "\n";
	}
	else
	{
		std::cout << "ERROR:: -SHADER- COULD NOT OPEN FILE: " << fileName << std::endl;
	}

	in_file.close();

	std::string version = std::to_string(this->majorVersion) + std::to_string(this->minorVersion) + "0";
	src.replace(src.find("#version"), 12, ("#version " + version));

	return src;
}

GLuint Shader::loadShader(GLenum type, char* fileName)
{
	char infolog[512];
	GLint success;

	GLuint shader = glCreateShader(type);
	std::string str_src = this->loadShaderSource(fileName);
	const GLchar *src = str_src.c_str();
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infolog);
		std::cout << "ERROR:: -SHADER- COULD NOT COMPILE SHADER: " << fileName << std::endl;
		std::cout << infolog << std::endl;
	}
	return shader;
}

void Shader::linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
{
	char infolog[512];
	GLint success;

	this->id = glCreateProgram();

	glAttachShader(this->id, vertexShader);

	if (geometryShader)
		glAttachShader(this->id, geometryShader);

	glAttachShader(this->id, fragmentShader);

	glLinkProgram(this->id);

	glGetProgramiv(this->id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->id, 512, NULL, infolog);
		std::cout << "ERROR:: -SHADER- COULD NOT LINK PGROGRAM" << std::endl;
		std::cout << infolog << std::endl;
	}
	glUseProgram(0);
}

Shader::Shader(const int majorVersion, const int minorVersion, const char* cVertexFile, const char* cFragmentFile, const char* cGeometryFile)
	: majorVersion(majorVersion), minorVersion(minorVersion)
{
	GLuint vertexShader = 0;
	GLuint geometryShader = 0;
	GLuint fragmentShader = 0;
	
	char *vertexFile, *fragmentFile, *geometryFile;
	vertexFile = (char*)cVertexFile;
	fragmentFile = (char*)cFragmentFile;
	geometryFile = (char*)cGeometryFile;

	vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);

	if (geometryFile != "")
		geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);

	fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

	this->linkProgram(vertexShader, geometryShader, fragmentShader);

	// END
	glDeleteShader(vertexShader);
	glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);
}
Shader::~Shader()
{
	glDeleteProgram(this->id);
}

void Shader::use()
{
	glUseProgram(this->id);
}

void Shader::unuse()
{
	glUseProgram(0);
}

void Shader::setBool(bool value, const GLchar* name)
{
	this->use();

	glUniform1f(glGetUniformLocation(this->id, name), value);

	this->unuse();
}

void Shader::setInt(int value, const GLchar* name)
{
	this->use();

	glUniform1f(glGetUniformLocation(this->id, name), value);

	this->unuse();
}

void Shader::setFloat(float value, const GLchar* name)
{
	this->use();

	glUniform1f(glGetUniformLocation(this->id, name), value);

	this->unuse();
}

void Shader::set1i(GLfloat value, const GLchar* name)
{
	this->use();

	glUniform1f(glGetUniformLocation(this->id, name), value);

	this->unuse();
}

void Shader::setVec2f(glm::fvec2 value, const GLchar* name)
{
	this->use();

	glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

	this->unuse();
}

void Shader::setVec3f(glm::fvec3 value, const GLchar* name)
{
	this->use();

	glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

	this->unuse();
}

void Shader::setVec4f(glm::fvec4 value, const GLchar* name)
{
	this->use();

	glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

	this->unuse();
}

void Shader::setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose)
{
	this->use();

	glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(value));

	this->unuse();
}

void Shader::setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose)
{
	this->use();

	glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(value));

	this->unuse();
}