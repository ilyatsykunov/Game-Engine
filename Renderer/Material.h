#pragma once
#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include <GLM\glm.hpp>
#include <GLM\vec2.hpp>
#include <GLM\vec3.hpp>
#include <GLM\vec4.hpp>
#include <GLM\mat4x4.hpp>
#include <GLM\gtc\type_ptr.hpp>

#include "Shader.h"

/*
	Material class sends material and lighting data to the fragment shader
*/

class Material
{
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLint diffuseTex;
	GLint specularTex;

public:
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTex, GLint specularTex);
	~Material();
	void sendToShader(Shader&);
};

