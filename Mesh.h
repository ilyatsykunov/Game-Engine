#pragma once

#include <iostream>
#include <vector>

#include "Primitives.h"
#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"

class Mesh
{
private:
	Vertex* vertexArray;
	unsigned nrOfVertices;
	GLuint* indexArray;
	unsigned nrOfIndices;

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
	void updateUniforms(Shader *);
public:
	Mesh(Vertex *, const unsigned &, GLuint *, const unsigned &, glm::vec3, glm::vec3, glm::vec3, glm::vec3);
	Mesh(Primitive *, glm::vec3, glm::vec3, glm::vec3, glm::vec3);
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
	void render(Shader *);
};

