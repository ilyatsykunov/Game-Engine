#include "Model.h"



void Model::updateUniforms()
{
}

Model::Model(glm::vec3 position, Material* material, Texture* orTexDif, Texture* orTexSpec, std::vector<Mesh*> meshes)
{
	this->position = position;
	this->material = material;
	this->overrideTextureDiffuse = orTexDif;
	this->overrideTextureSpecular = orTexSpec;

	for (auto* i : meshes)
		this->meshes.push_back(new Mesh(*i));

	for (auto& i : this->meshes)
	{
		i->setOrigin(this->position);
		i->move(this->position);
	}
}


Model::~Model()
{
	for (auto*& i : this->meshes)
		delete i;
}

void Model::rotate(const glm::vec3 rotation)
{
	for (auto& i : this->meshes)
		i->rotate(rotation);
}

void Model::render(Shader* shader)
{
	// UPDATE UNIFORMS
	this->updateUniforms();
	this->material->sendToShader(*shader);

	// USE THE PROGRAM
	shader->use();

	// ACTIVATE TEXTURE
	this->overrideTextureDiffuse->bind(0);
	this->overrideTextureSpecular->bind(1);

	// DRAW
	for (auto& i : this->meshes)
		i->render(shader);
}
