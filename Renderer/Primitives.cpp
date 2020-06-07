#include "Primitives.h"

/*
	Class of primitive shapes: Quad, Triangle, Pyramid and Cube
*/

Primitive::Primitive()
{
}


Primitive::~Primitive()
{
}

void Primitive::set(const Vertex* vertices, const unsigned nrOfVertices, const GLuint *indices, const unsigned nrOfIndices)
{
	for (size_t i = 0; i < nrOfVertices; i++)
	{
		this->vertices.push_back(vertices[i]);
	}
	for (size_t i = 0; i < nrOfIndices; i++)
	{
		this->indices.push_back(indices[i]);
	}
}

Quad::Quad() 
	: Primitive()
{
	Vertex vertices[] =
	{
		//Location									//Color										//Texcoords									//Normals						
		glm::vec3(-0.5f, 0.5f, 0.0f),				glm::vec3(1.0f, 0.0f, 0.0f),				glm::vec2(0.0f, 1.0f),						glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),				glm::vec3(0.0f, 1.0f, 0.0f),				glm::vec2(0.0f, 0.0f),						glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.5f, -0.5f, 0.0f),				glm::vec3(0.0f, 0.0f, 1.0f),				glm::vec2(1.0f, 0.0f),						glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.5f, 0.5f, 0.0f),				glm::vec3(0.0f, 1.0f, 0.0f),				glm::vec2(1.0f, 1.0f),						glm::vec3(0.0f, 0.0f, 1.0f)

	};

	unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

	this->set(vertices, nrOfVertices, indices, nrOfIndices);
}

Triangle::Triangle()
	: Primitive()
{
	Vertex vertices[] =
	{
		//Location									//Color										//Texcoords									//Normals						
		glm::vec3(-0.5f, 0.5f, 0.0f),				glm::vec3(1.0f, 0.0f, 0.0f),				glm::vec2(0.0f, 1.0f),						glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),				glm::vec3(0.0f, 1.0f, 0.0f),				glm::vec2(0.0f, 0.0f),						glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.5f, -0.5f, 0.0f),				glm::vec3(0.0f, 0.0f, 1.0f),				glm::vec2(1.0f, 0.0f),						glm::vec3(0.0f, 0.0f, 1.0f)
	};

	unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

	GLuint indices[] =
	{
		0, 1, 2
	};

	unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

	this->set(vertices, nrOfVertices, indices, nrOfIndices);
}

Pyramid::Pyramid()
{
	Vertex vertices[] =
	{
		//Triangle front
		//Location									//Color										//Texcoords									//Normals						
		glm::vec3(0.0f, 0.5f, 0.0f),				glm::vec3(1.0f, 1.0f, 0.0f),				glm::vec2(0.5f, 1.0f),						glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-0.5f, -0.5, 0.5f),				glm::vec3(0.0f, 0.0f, 1.0f),				glm::vec2(0.0f, 0.0f),						glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.5f, -0.5f, 0.5f),				glm::vec3(0.0f, 0.0f, 1.0f),				glm::vec2(1.0f, 0.0f),						glm::vec3(0.0f, 0.0f, 1.0f),
		//Triangle left
		glm::vec3(0.0f, 0.5f, 0.0f),				glm::vec3(1.0f, 1.0f, 0.0f),				glm::vec2(0.5f, 1.0f),						glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-0.5f, -0.5, -0.5f),				glm::vec3(0.0f, 0.0f, 1.0f),				glm::vec2(0.0f, 0.0f),						glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.5f),				glm::vec3(0.0f, 0.0f, 1.0f),				glm::vec2(1.0f, 0.0f),						glm::vec3(-1.0f, 0.0f, 0.0f),
		//Triangle back
		glm::vec3(0.0f, 0.5f, 0.0f),				glm::vec3(1.0f, 1.0f, 0.0f),				glm::vec2(0.5f, 1.0f),						glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.5f, -0.5, -0.5f),				glm::vec3(0.0f, 0.0f, 1.0f),				glm::vec2(0.0f, 0.0f),						glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(-0.5f, -0.5f, -0.5f),				glm::vec3(0.0f, 0.0f, 1.0f),				glm::vec2(1.0f, 0.0f),						glm::vec3(0.0f, 0.0f, -1.0f),
		//Triangle right
		glm::vec3(0.0f, 0.5f, 0.0f),				glm::vec3(1.0f, 1.0f, 0.0f),				glm::vec2(0.5f, 1.0f),						glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.5f, -0.5, 0.5f),				glm::vec3(0.0f, 0.0f, 1.0f),				glm::vec2(0.0f, 0.0f),						glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.5f, -0.5f, -0.5f),				glm::vec3(0.0f, 0.0f, 1.0f),				glm::vec2(1.0f, 0.0f),						glm::vec3(1.0f, 0.0f, 0.0f)
	};

	unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

	this->set(vertices, nrOfVertices, nullptr, 0);
}

Cube::Cube()
	: Primitive()
{
	Vertex vertices[] =
	{
		//Cube front
		//Location									//Color										//Texcoords									//Normals						
		glm::vec3(-0.5f, 0.5f, 0.0f),				glm::vec3(1.0f, 0.0f, 0.0f),				glm::vec2(0.0f, 1.0f),						glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),				glm::vec3(0.0f, 1.0f, 0.0f),				glm::vec2(0.0f, 0.0f),						glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.5f, -0.5f, 0.0f),				glm::vec3(0.0f, 0.0f, 1.0f),				glm::vec2(1.0f, 0.0f),						glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.5f, 0.5f, 0.0f),				glm::vec3(0.0f, 1.0f, 0.0f),				glm::vec2(1.0f, 1.0f),						glm::vec3(0.0f, 0.0f, 1.0f),
		//Cube left
		glm::vec3(-0.5f, 0.5f, -1.0f),				glm::vec3(1.0f, 1.0f, 0.0f),				glm::vec2(0.0f, 1.0f),						glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-0.5f, -0.5f, -1.0f),				glm::vec3(0.0f, 0.0f, 0.0f),				glm::vec2(0.0f, 0.0f),						glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),				glm::vec3(0.0f, 0.0f, 1.0f),				glm::vec2(1.0f, 0.0f),						glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-0.5f, 0.5f, 0.0f),				glm::vec3(0.0f, 1.0f, 0.0f),				glm::vec2(1.0f, 1.0f),						glm::vec3(-1.0f, 0.0f, 0.0f),
		//Cube back			
		glm::vec3(0.5f, 0.5f, -1.0f),				glm::vec3(0.0f, 1.0f, 0.0f),				glm::vec2(0.0f, 1.0f),						glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.5f, -0.5f, -1.0f),				glm::vec3(1.0f, 0.0f, 0.0f),				glm::vec2(0.0f, 0.0f),						glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(-0.5f, -0.5f, -1.0f),				glm::vec3(0.0f, 0.0f, 1.0f),				glm::vec2(1.0f, 0.0f),						glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(-0.5f, 0.5f, -1.0f),				glm::vec3(0.0f, 1.0f, 0.0f),				glm::vec2(1.0f, 1.0f),						glm::vec3(0.0f, 0.0f, -1.0f),
		//Cube right
		glm::vec3(0.5f, 0.5f, 0.0f),				glm::vec3(1.0f, 1.0f, 0.0f),				glm::vec2(0.0f, 1.0f),						glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.0f),				glm::vec3(0.0f, 0.0f, 0.0f),				glm::vec2(0.0f, 0.0f),						glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.5f, -0.5f, -1.0f),				glm::vec3(0.0f, 0.0f, 1.0f),				glm::vec2(1.0f, 0.0f),						glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.5f, 0.5f, -1.0f),				glm::vec3(0.0f, 1.0f, 0.0f),				glm::vec2(1.0f, 1.0f),						glm::vec3(1.0f, 0.0f, 0.0f),
		//Cube top
		glm::vec3(-0.5f, 0.5f, -1.0f),				glm::vec3(1.0f, 1.0f, 0.0f),				glm::vec2(0.0f, 1.0f),						glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(-0.5f, 0.5f, 0.0f),				glm::vec3(0.0f, 0.0f, 0.0f),				glm::vec2(0.0f, 0.0f),						glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.5f, 0.5f, 0.0f),				glm::vec3(0.0f, 0.0f, 1.0f),				glm::vec2(1.0f, 0.0f),						glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.5f, 0.5f, -1.0f),				glm::vec3(0.0f, 1.0f, 0.0f),				glm::vec2(1.0f, 1.0f),						glm::vec3(0.0f, 1.0f, 0.0f),
		//Cube bottom
		glm::vec3(0.5f, -0.5f, -1.0f),				glm::vec3(1.0f, 1.0f, 0.0f),				glm::vec2(0.0f, 1.0f),						glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.0f),				glm::vec3(0.0f, 0.0f, 0.0f),				glm::vec2(0.0f, 0.0f),						glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),				glm::vec3(0.0f, 0.0f, 1.0f),				glm::vec2(1.0f, 0.0f),						glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(-0.5f, -0.5f, -1.0f),				glm::vec3(0.0f, 1.0f, 0.0f),				glm::vec2(1.0f, 1.0f),						glm::vec3(0.0f, -1.0f, 0.0f)
	};

	unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

	GLuint indices[] =
	{
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};

	unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

	this->set(vertices, nrOfVertices, indices, nrOfIndices);
}