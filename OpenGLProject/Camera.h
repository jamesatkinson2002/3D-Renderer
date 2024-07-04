#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera {
private:
	float pitch, yaw, lastX, lastY;
	bool firstMouse;
	glm::vec3 cameraPos, cameraFront, cameraUp;
	const float sensitivity = 0.1f;
public:
	Camera(float width, float height, const glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::vec3& cameraUp);
	void handleKeyInput(GLFWwindow* window, float deltaTime);
	void handleMouseInput(double xpos, double ypos);
	const glm::mat4& lookAt();
	const glm::vec3& getCameraPos() const;
	const glm::vec3& getCameraDirection() const;

};