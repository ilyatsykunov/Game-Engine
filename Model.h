#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"


class Model
{
private:
	Material *material;
	Texture *overrideTextureDiffuse;
	Texture *overrideTextureSpecular;
	std::vector<Mesh*> meshes;
	glm::vec3 position;

	void updateUniforms();
public:
	Model(glm::vec3, Material*, Texture*, Texture*, std::vector<Mesh*>);
	~Model();

	void rotate(const glm::vec3);

	void update();
	void render(Shader*);
};

