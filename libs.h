#pragma once

/*
	All libraries required by the Game class
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include <GLM\glm.hpp>
#include <GLM\vec2.hpp>
#include <GLM\vec3.hpp>
#include <GLM\vec4.hpp>
#include <GLM\mat4x4.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>

#include <SOIL2\SOIL2.h>

#include <assimp/aabb.h>

#include "Renderer/Vertex.h"
#include "Renderer/Primitives.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Material.h"
#include "Renderer/Mesh.h"
#include "Renderer/Camera.h"
#include "Renderer/Model.h"