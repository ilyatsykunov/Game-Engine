#pragma once

#include <iostream>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>

enum direction { FORWARD = 0, BACKWARD, LEFT, RIGHT };

class Camera
{
private:
	glm::mat4 ViewMatrix;

	GLfloat movementSpeed;
	GLfloat sensitivity;

	glm::vec3 worldUp;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;

	// ACCESSORS

	// MODIFIERS
	void updateCameraVectors();

	// FUNCTIONS

public:
	Camera(glm::vec3, glm::vec3, glm::vec3);
	~Camera();

	// ACCESSORS
	const glm::mat4 getViewMatrix();

	const glm::vec3 getPosition() const;

	// MODIFIERS

	// FUNCTIONS
	void move(const float &, const int);
	void updateMouseInput(const float &, const double &, const double &);
	void updateInput(const float &, const int, const double &, const double &);
};

