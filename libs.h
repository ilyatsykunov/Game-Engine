#pragma once

/*
	All libraries required by the Game class
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include <SOIL2.h>

#include "Renderer/Vertex.h"
#include "Renderer/Primitives.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Material.h"
#include "Renderer/Mesh.h"
#include "Renderer/Camera.h"
#include "Renderer/Model.h"