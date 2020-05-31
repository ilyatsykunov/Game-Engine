#pragma once

#include "libs.h"

// ENUMERATIONS
enum shader_enum { SHADER_CORE_PROGRAM = 0 };
enum texture_enum { TEXTURE0 = 0, TEXTURE0_SPECULAR};
enum material_enum { MATERIAL1 = 0 };
enum mesh_enum { MESH_QUAD = 0 };

class Game
{
private:
	// Window
	GLFWwindow *window;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int framebufferWidth;
	int framebufferHeight;

	// OpenGL context
	const int GL_MAJOR_V;
	const int GL_MINOR_V;

	// Delta time
	float dt;
	float curTime;
	float lastTime;

	// Mouse input
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;

	// Camera
	Camera camera;

	// Matrices
	glm::mat4 ViewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;
	glm::mat4 ProjectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;


	// Shaders
	std::vector<Shader*> shaders;

	// Textures
	std::vector<Texture*> textures;

	// Materials
	std::vector<Material*> materials;

	// Models
	std::vector<Model*> models;

	// Lights
	std::vector<glm::vec3*> lights;

	// PRIVATE FUNCTIONS
	void initGLFW();
	void initWindow(const char *, bool);
	void initGLEW();
	void initOpenGLOptions();
	void initMatrices();
	void initShaders();
	void initTextures();
	void initMaterials();
	void initModels();
	void initLights();
	void initUniforms();

	void updateUniforms();

public:
	Game(const char *, const int, const int, int, int, bool);
	~Game();

	// ACCESSORS
	int getWindowShouldClose();

	// MODIFIERS
	void setWindowShouldClose();

	// FUNCTIONS
	void updateDt();
	void updateMouseInput();
	void updateKeyboardInput();
	void updateInput();
	void update();
	void render();

	//STATIC FUNCTIONS
	static void framebufferResizeCallback(GLFWwindow *, int, int);
};

