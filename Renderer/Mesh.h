#pragma once

#include <iostream>
#include <vector>

#include "Primitives.h"
#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"

/*
	Class for loading mesh data into memory
*/

class Mesh
{
private:
	Vertex* vertexArray;
	unsigned int nrOfVertices;
	GLuint* indexArray;
	unsigned int nrOfIndices;
	std::vector<Texture*> textureArray;
	unsigned int nrOfTextures;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 origin;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 ModelMatrix;

	void initVAO();
	void updateModelMatrix();
	void updateUniforms(Shader*);
public:
	Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices, 
		glm::vec3 position, glm::vec3 origin, glm::vec3 rotation, glm::vec3 scale);
	Mesh(Primitive* primitive, glm::vec3 origin, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	Mesh(std::vector<Vertex> vertexArray, std::vector<GLuint> indexArray, std::vector<Texture*> textureArray);
	Mesh(const Mesh&);
	~Mesh();
	// Modifiers
	void setPosition(const glm::vec3 position);
	void setOrigin(const glm::vec3 origin);
	void setRotation(const glm::vec3 roration);
	void setScale(const glm::vec3 scale);

	void move(const glm::vec3 position);
	void rotate(const glm::vec3 rotation);
	void scaleUp(const glm::vec3 scale);


	void update();
	void render(Shader*);
};

