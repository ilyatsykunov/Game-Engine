#pragma once

#include <glew.h>
#include <glfw3.h>

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

	void set(const Vertex *, const unsigned, const GLuint *, const unsigned);
	inline Vertex *getVertices() { return this->vertices.data(); }
	inline GLuint *getIndices() { return this->indices.data(); }
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