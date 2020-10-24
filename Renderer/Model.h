#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	Model(glm::vec3 position, Material* material, Texture* orTexDif, Texture* orTexSpec, std::vector<Mesh*> meshArray);
	Model(const GLchar* path) { this->loadModel(path); }
	~Model();

	void rotate(const glm::vec3);

	void render(Shader*);

private:
	Material* material;
	Texture* overrideTextureDiffuse;
	Texture* overrideTextureSpecular;
	std::vector<Mesh*> meshes;
	std::vector<Texture*> loadedTextures;
	glm::vec3 position;

	std::string directory;

	void loadModel(std::string path);
	// Recursively converts all nodes in a aiScene into Mesh objects
	void processNode(aiNode* node, const aiScene* scene);
	// Converts aiMesh object into our Mesh object
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene); 
	std::vector<Texture*> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

