#include "Game.h"

void Game::initGLFW()
{
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "ERROR: -GLFW INIT- FAILED" << std::endl;
	}
}

void Game::initWindow(const char *title, bool resizable)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_MAJOR_V);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_MINOR_V);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);

	if (this->window == nullptr)
	{
		std::cout << "ERROR: -initWindow- FAILED" << std::endl;
		glfwTerminate();
	}

	glfwSetFramebufferSizeCallback(this->window, Game::framebufferResizeCallback);

	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	glViewport(0, 0, this->framebufferWidth, this->framebufferHeight);

	glfwMakeContextCurrent(this->window); // IMPORTANT
}

void Game::initGLEW()
{
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR: -initGLEW- FAILED" << std::endl;
		glfwTerminate();
	}
}

void Game::initOpenGLOptions()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::initMatrices()
{
	this->ViewMatrix = glm::mat4(1.0f);
	this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

	this->ProjectionMatrix = glm::mat4(1.0f);
	this->ProjectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->framebufferWidth) / this->framebufferHeight, this->nearPlane, this->farPlane);
}

void Game::initShaders()
{
	// MAIN SHADER
	Shader *newShader = new Shader(this->GL_MAJOR_V, this->GL_MINOR_V, "vertex_core.glsl", "fragment_core.glsl");
	shaders.push_back(newShader);
}

void Game::initTextures()
{
	Texture *newTexture0 = new Texture("Images/test.jpg", GL_TEXTURE_2D);
	this->textures.push_back(newTexture0);
	Texture *newTexture0Specular = new Texture("Images/testSpecular.jpg", GL_TEXTURE_2D);
	this->textures.push_back(newTexture0Specular);
}

void Game::initMaterials()
{
	Material *newMaterial0 = new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 0, 1);
	this->materials.push_back(newMaterial0);
}

void Game::initModels()
{
	std::vector<Mesh*> meshes;

	Mesh *groundMesh1 = new Mesh(&Cube(), glm::vec3(0.0f), glm::vec3(0.0f, -0.75f, 5.0f), glm::vec3(0.0f), glm::vec3(50.0f, 0.5f, 50.0f));
	meshes.push_back(groundMesh1);
	Model* groundModel1 = new Model(glm::vec3(0.0f), this->materials[0], this->textures[TEXTURE0], this->textures[TEXTURE0_SPECULAR], meshes);
	this->models.push_back(groundModel1);

	Mesh *lampMesh1 = new Mesh(&Cube(), glm::vec3(0.0f), glm::vec3(-2.0f, 0.0f, 2.0f), glm::vec3(0.0f), glm::vec3(0.25f, 5.0f, 0.25f));
	meshes.push_back(lampMesh1);
	Model* lampModel1 = new Model(glm::vec3(0.0f), this->materials[0], this->textures[TEXTURE0], this->textures[TEXTURE0_SPECULAR], meshes);
	this->models.push_back(lampModel1);

	for (int i = 0; i < 3; i++)
	{
		Mesh *cubeMesh1 = new Mesh(&Cube(), glm::vec3(0.0f), glm::vec3(-1.5f * i, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
		meshes.push_back(cubeMesh1);
		Model* cubeModel1 = new Model(glm::vec3(0.0f), this->materials[0], this->textures[TEXTURE0], this->textures[TEXTURE0_SPECULAR], meshes);
		this->models.push_back(cubeModel1);

		Mesh *pyramidMesh1 = new Mesh(&Pyramid(), glm::vec3(0.0f), glm::vec3(-1.5f * i, 1.0f, -0.5f), glm::vec3(0.0f), glm::vec3(1.0f));
		meshes.push_back(pyramidMesh1);
		Model* pyramidModel1 = new Model(glm::vec3(0.0f), this->materials[0], this->textures[TEXTURE0], this->textures[TEXTURE0_SPECULAR], meshes);
		this->models.push_back(pyramidModel1);
	}

	for (int i = 0; i < 10; i++)
	{
		Mesh *cubeMesh1 = new Mesh(&Cube(), glm::vec3(0.0f), glm::vec3(1.5f * i, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
		meshes.push_back(cubeMesh1);
		Model* cubeModel1 = new Model(glm::vec3(0.0f), this->materials[0], this->textures[TEXTURE0], this->textures[TEXTURE0_SPECULAR], meshes);
		this->models.push_back(cubeModel1);

		Mesh *pyramidMesh1 = new Mesh(&Pyramid(), glm::vec3(0.0f), glm::vec3(1.5f * i, 1.0f, -0.5f), glm::vec3(0.0f), glm::vec3(1.0f));
		meshes.push_back(pyramidMesh1);
		Model* pyramidModel1 = new Model(glm::vec3(0.0f), this->materials[0], this->textures[TEXTURE0], this->textures[TEXTURE0_SPECULAR], meshes);
		this->models.push_back(pyramidModel1);
	}


	for (auto*& i : meshes)
		delete i;
}

void Game::initLights()
{
	glm::vec3 *newLightPos0 = new glm::vec3(-2.0f, 0.0f, 2.0f);
	this->lights.push_back(newLightPos0);
}

void Game::initUniforms()
{
	Shader* lightingShader = this->shaders[SHADER_CORE_PROGRAM];
	lightingShader->setMat4fv(ViewMatrix, "ViewMatrix");
	lightingShader->setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	// MAIIN LIGHT
	lightingShader->setVec3f(*this->lights[0], "light.position");
	lightingShader->setVec3f(glm::vec3(-0.0f, -3.0f, -5.0f), "light.direction");
	lightingShader->setFloat(glm::cos(glm::radians(12.5f)), "light.cutOff");

	lightingShader->setVec3f(glm::vec3(2.0f, 2.0f, 2.0f), "light.ambient");
	lightingShader->setVec3f(glm::vec3(0.5f, 0.5f, 0.5f), "light.diffuse");
	lightingShader->setVec3f(glm::vec3(2.0f, 2.0f, 2.0f), "light.specular");

	lightingShader->setFloat(1.0f, "light.constant");
	lightingShader->setFloat(0.1f, "light.linear");
	lightingShader->setFloat(0.01f, "light.quadratic");

}

void Game::updateUniforms()
{
	// UPDATE CAMERA VIEW MATRIX
	this->ViewMatrix = this->camera.getViewMatrix();

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "cameraPos");

	// UPDATE FRAMEBUFFER SIZE AND PROJECTION MATRIX
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

	this->ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(this->framebufferWidth) / this->framebufferHeight, this->nearPlane, this->farPlane);

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ProjectionMatrix, "ProjectionMatrix");
}

Game::Game(const char *title, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, int GL_MAJOR_V, int GL_MINOR_V, bool resizable)
	: WINDOW_WIDTH(WINDOW_WIDTH), WINDOW_HEIGHT(WINDOW_HEIGHT), GL_MAJOR_V(GL_MAJOR_V), GL_MINOR_V(GL_MINOR_V), 
	camera(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f))
{
	this->window = nullptr;
	this->framebufferWidth = WINDOW_WIDTH;
	this->framebufferHeight = WINDOW_HEIGHT;

	this->camPosition = glm::vec3(0.0f, 0.0f, 1.0f);
	this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->camFront = glm::vec3(0.0f, 0.0f, -1.0f);

	this->fov = 90.0f;
	this->nearPlane = 0.1f;
	this->farPlane = 1000.0f;

	this->dt = 0.0f;
	this->curTime = 0.0f;
	this->lastTime = 0.0f;

	this->lastMouseX = 0.0f;
	this->lastMouseY = 0.0f;
	this->mouseX = 0.0f;
	this->mouseY = 0.0f;
	this->mouseOffsetX = 0.0f;
	this->mouseOffsetY = 0.0f;
	this->firstMouse = true;

	this->initGLFW();
	this->initWindow(title, resizable);
	this->initGLEW();
	this->initOpenGLOptions();
	this->initMatrices();
	this->initShaders();
	this->initTextures();
	this->initMaterials();
	this->initModels();
	this->initLights();
	this->initUniforms();
}

Game::~Game()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();

	for (size_t i = 0; i < this->shaders.size(); i++)
		delete this->shaders[i];
	for (size_t i = 0; i < this->textures.size(); i++)
		delete this->textures[i];
	for (size_t i = 0; i < this->materials.size(); i++)
		delete this->materials[i];
	for (auto*& i : this->models)
		delete i;
	for (size_t i = 0; i < this->lights.size(); i++)
		delete this->lights[i];
}

int Game::getWindowShouldClose()
{
	return glfwWindowShouldClose(this->window);
}

void Game::setWindowShouldClose()
{
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

void Game::updateDt()
{
	this->curTime = static_cast<float>(glfwGetTime());
	this->dt = this->curTime - this->lastTime;
	this->lastTime = this->curTime;
}

void Game::updateMouseInput()
{
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

	if (this->firstMouse)
	{
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
	}

	// Calculate offset
	this->mouseOffsetX = this->mouseX - this->lastMouseX;
	this->mouseOffsetY = this->lastMouseY - this->mouseY;

	//Set last X and Y
	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;

}

void Game::updateKeyboardInput()
{
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		this->setWindowShouldClose();

	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
		this->camera.move(this->dt, FORWARD);
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
		this->camera.move(this->dt, BACKWARD);
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
		this->camera.move(this->dt, LEFT);
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
		this->camera.move(this->dt, RIGHT);
}

void Game::updateInput()
{
	glfwPollEvents();

	this->updateKeyboardInput();
	this->updateMouseInput();
	this->camera.updateInput(dt, -1, this->mouseOffsetX, this->mouseOffsetY);
}

void Game::update()
{
	// UPDATE INPUT
	updateDt();
	updateInput();
}

void Game::render()
{
	updateInput();
	// CLEAR
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// UPDATE UNIFORMS
	this->updateUniforms();

	// RENDER MODELS
	for(auto& i : this->models)
		i->render(this->shaders[SHADER_CORE_PROGRAM]);

	// END DRAW
	glfwSwapBuffers(window);
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Game::framebufferResizeCallback(GLFWwindow *window, int fbW, int fbH)
{
	glViewport(0, 0, fbW, fbH);
};
