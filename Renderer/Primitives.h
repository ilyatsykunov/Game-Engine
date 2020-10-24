#pragma once

/*
	Class of primitive shapes: Quad, Triangle, Pyramid and Cube
*/

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include <vector>
#include "Vertex.h"

class Primitive
{
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;


public:
	Primitive();
	virtual ~Primitive();

	void set(const Vertex* vertices, const unsigned nrOfVertices, const GLuint *indices, const unsigned nrOfIndices);
	inline Vertex* getVertices() { return this->vertices.data(); }
	inline GLuint* getIndices() { return this->indices.data(); }
	inline const unsigned getNrOfVertices() { return this->vertices.size(); }
	inline const unsigned getNrOfIndices() { return this->indices.size(); }
};

class Quad : public Primitive
{
public:
	Quad();
};

class Triangle : public Primitive
{
public:
	Triangle();
};

class Pyramid : public Primitive
{
public:
	Pyramid();
};

class Cube : public Primitive
{
public:
	Cube();
};