#include "Model.h"


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
	//this->updateUniforms();
	this->material->sendToShader(*shader);

	// USE THE PROGRAM
	shader->use();

	// ACTIVATE TEXTURES
	for (auto& i : this->loadedTextures)
		i->bind(i->getType());

	// DRAW
	for (auto& i : this->meshes)
		i->render(shader);
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
	}

	this->directory = path.substr(0, path.find_last_of('\\'));
	this->processNode(scene->mRootNode, scene);

	this->material = new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 0, 1);
}

// Recursively converts all nodes in a aiScene into Mesh objects
void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->processMesh(mesh, scene));
	}

	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}
}

// Converts aiMesh object into our Mesh object
Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture*> textures;

	// Process vertex positions
	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		if (mesh->mTextureCoords[0])
			vertex.texcoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		else
			vertex.texcoord = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	// Process indices
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// Process material
	if (mesh->mMaterialIndex >= 0)
	{
		// THE ARRAY GETS MESSED UP AND TEXTURES ARE SWITCHED AROUND
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture*> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		
		std::vector<Texture*> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return new Mesh(vertices, indices, textures);
}

std::vector<Texture*> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture*> textures = {};
	
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString fileName;
		mat->GetTexture(type, i, &fileName);
		bool bTextureLoaded = false;

		//std::cout << " this filename: " << std::string(fileName.C_Str()) << std::endl;


		// check if the texture has previously been loaded. If true - reuse existing texture
		for (GLuint j = 0; j < this->loadedTextures.size(); j++)
		{
			if (std::strcmp(this->loadedTextures[j]->getName(), fileName.C_Str()) == 0)
			{
				textures.push_back(loadedTextures[j]);
				bTextureLoaded = true;
				break;
			}
		}

		// If false - load new texture
		if (!bTextureLoaded)
		{
			GLchar* newFileName = _strdup(fileName.C_Str());
			std::string texPath = this->directory + "\\" + std::string(newFileName);
			Texture* newTexture = new Texture(newFileName, texPath.c_str(), typeName);
			textures.push_back(newTexture);
			this->loadedTextures.push_back(newTexture);
		}
	}

	return textures;
}
