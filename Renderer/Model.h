#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"


class Model
{
private:
	Material* material;
	Texture* overrideTextureDiffuse;
	Texture* overrideTextureSpecular;
	std::vector<Mesh*> meshes;
	glm::vec3 position;

public:
	Model(glm::vec3 position, Material* material, Texture* orTexDif, Texture* orTexSpec, std::vector<Mesh*> meshes);
	~Model();

	void rotate(const glm::vec3);

	void render(Shader*);
};

