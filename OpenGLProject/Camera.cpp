#include "Camera.h"

Camera::Camera(float width, float height, const glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::vec3& cameraUp) 
	: pitch {
	0.0f
}, yaw{ -90.0f }, lastX{ width/2 }, lastY{ height/ 2}, cameraPos{
	cameraPos }, cameraFront{ cameraFront }, cameraUp{ cameraUp }, firstMouse{ true } {
}

void Camera::handleKeyInput(GLFWwindow* window, float deltaTime) {
	float cameraSpeed = deltaTime * 2.5f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	//for true fps camera
	//cameraPos.y = 0.0f;
}

void Camera::handleMouseInput(double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}

const glm::mat4& Camera::lookAt() {
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	return view;
}

const glm::vec3& Camera::getCameraPos() const {
	return cameraPos;
}

const glm::vec3& Camera::getCameraDirection() const {
	return cameraFront;
}
