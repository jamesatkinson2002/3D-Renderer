#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "ShaderManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Camera.h"
using namespace std;

static constexpr int WIDTH = 1280;
static constexpr int HEIGHT = 720;

bool firstMouse = true;

float mixValue = 0.0f;

float fov = 45.0f;

//function is called when the window is resized.
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

Camera camera((float)WIDTH, (float)HEIGHT, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

float deltaTime = 0.0f;
float lastTime = 0.0f;

float lastX = WIDTH / 2;
float lastY = HEIGHT / 2;

glm::vec3 lightPos(1.2f, 0.5f, 2.0f);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

static float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

static unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

glm::vec3 cubePositions[] = {
glm::vec3(0.0f,  0.0f,  0.0f),
glm::vec3(2.0f,  5.0f, -15.0f),
glm::vec3(-1.5f, -2.2f, -2.5f),
glm::vec3(-3.8f, -2.0f, -12.3f),
glm::vec3(2.4f, -0.4f, -3.5f),
glm::vec3(-1.7f,  3.0f, -7.5f),
glm::vec3(1.3f, -2.0f, -2.5f),
glm::vec3(1.5f,  2.0f, -2.5f),
glm::vec3(1.5f,  0.2f, -1.5f),
glm::vec3(-1.3f,  1.0f, -1.5f)
};

unsigned int vaoID, vboID, eboID;
unsigned int lightVaoID;
ShaderManager* shaderManager;
ShaderManager* lightSourceShader;

unsigned int diffuseMap, specularMap, emissionMap;
GLFWwindow* window;

bool loadTexture(unsigned int& textureId, const char* path) {
	glGenTextures(1, &textureId);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (!data) {
		cout << "Failed to load texture!" << endl;
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, textureId);

	switch (nrChannels) {
	case 3:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		break;
	case 4:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		break;
	default:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		break;
	}

	stbi_image_free(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/*
	float borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	*/

	stbi_set_flip_vertically_on_load(true);
	return true;
}

//initializes window and opengl context
bool init() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	window = glfwCreateWindow(WIDTH, HEIGHT, "the best renderer ever", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create GLFW Window." << endl;
		return false;
	}

	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glViewport(0, 0, WIDTH, HEIGHT);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	shaderManager = new ShaderManager("shaders/vertLightSource.vert", "shaders/fragBasicLighting.frag");

	lightSourceShader = new ShaderManager("shaders/vertLightSource.vert", "shaders/fragLightSource.frag");
	
	glGenVertexArrays(1, &lightVaoID);
	glBindVertexArray(lightVaoID);

	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	bool diffuseTexture = loadTexture(diffuseMap, "res/container2.png");
	bool specularTexture = loadTexture(specularMap, "res/container2_specular.png");
	bool emissionTexture = loadTexture(emissionMap, "res/matrix.jpg");

	/*
	int numAttribs;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttribs);
	cout << "Number of vertex attributes available: " << numAttribs << endl;
	*/
	shaderManager->use();

	/*
		glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 right = glm::normalize(glm::cross(up, cameraDirection));

		glm::vec3 cameraUp = glm::cross(cameraDirection, right);
	*/

	return true;

}

//handles user input
void input() {
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastTime;
	lastTime = currentFrame;

	float cameraSpeed = 2.5f * deltaTime;
/*
	if (mixValue <= 0.0f)
		mixValue = 0.0f;
	else if (mixValue >= 1.0f)
		mixValue = 1.0f;
*/
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		mixValue += 0.0001f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		mixValue -= 0.0001f;
	}
	camera.handleKeyInput(window, deltaTime);
}

void render() {
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.1f, 0.4f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 view = camera.lookAt();

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(fov), static_cast<float>(WIDTH) / static_cast<float>(HEIGHT), 0.1f, 100.0f);

	shaderManager->use();

	glBindVertexArray(lightVaoID);

/*
	glm::vec3 lightColor;
	lightColor.x = sin(glfwGetTime() * 2.0f);
	lightColor.y = sin(glfwGetTime() * 0.7f);
	lightColor.z = sin(glfwGetTime() * 1.3f);
*/
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
	glm::vec3 ambientColor = lightColor * glm::vec3(0.2f);

	shaderManager->setUniformVec3f("light.ambient", ambientColor);
	shaderManager->setUniformVec3f("light.diffuse", diffuseColor);

	//shaderManager->setUniformVec3f("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	//shaderManager->setUniformVec3f("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	shaderManager->setUniformVec3f("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

	shaderManager->setUniformVec3f("light.position", lightPos);

	shaderManager->setUniformVec3f("viewPos", camera.getCameraPos());
	
	//for the material struct
	shaderManager->setUniformFloat("material.shininess", 32);

	shaderManager->setUniformInt("material.diffuse", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);

	shaderManager->setUniformInt("material.specular", 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap);

	shaderManager->setUniformInt("material.emission", 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, emissionMap);

	shaderManager->setUniformVec3f("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));

	for (unsigned int i = 0; i < 10; i++) {
		float angle = glm::radians(20.0f * i);

		if (i % 3 == 0)
			angle = (float)glfwGetTime();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
		shaderManager->setUniformMat4f("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	//model = glm::rotate(model, ((float)glfwGetTime()), glm::vec3(1.0f, 0.0f, 1.0f));

	shaderManager->setUniformMat4f("view", view);
	shaderManager->setUniformMat4f("projection", projection);

	/*
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));
	lightSourceShader->use();

	lightSourceShader->setUniformMat4f("model", model);
	lightSourceShader->setUniformMat4f("view", view);
	lightSourceShader->setUniformMat4f("projection", projection);

	lightSourceShader->setUniformVec3f("lightSourceColor", lightColor);

	glDrawArrays(GL_TRIANGLES, 0, 36);
*/

}
void clean() {
	glfwTerminate();
}

int main(int argc, char** argv) {
	if (!init())
		return -1;

	while (!glfwWindowShouldClose(window)) {
		input();
		render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	clean();
	return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	camera.handleMouseInput(xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}


