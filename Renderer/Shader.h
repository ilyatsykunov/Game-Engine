#pragma once

/*
	Class for loading and updating Vertext and Fragment shaders.
*/

#include <iostream>
#include <fstream>
#include <string>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc\type_ptr.hpp>

class Shader
{
private:
	GLuint id;
	int majorVersion;
	int minorVersion;

	std::string loadShaderSource(char* fileName);

	GLuint loadShader(GLenum type, char* fileName);

	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader);

public:

	Shader(const int majorVersion, const int minorVersion, const char* cVertexFile, const char* cFragmentFile, const char* cGeometryFile = "");
	~Shader();

	void use();

	void unuse();

	void setBool(bool value, const GLchar * name);
	void setInt(int value, const GLchar* name);
	void setFloat(float value, const GLchar* name);

	void set1i(GLfloat value, const GLchar* name);
	void setVec2f(glm::fvec2 value, const GLchar* name);
	void setVec3f(glm::fvec3 value, const GLchar* name);
	void setVec4f(glm::fvec4 value, const GLchar* name);
	void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE);
	void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);
};