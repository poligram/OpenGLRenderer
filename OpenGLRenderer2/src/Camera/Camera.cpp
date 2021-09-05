#include "Camera.h"

#include <gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 intialPosition, float pitch, float yaw, float roll, float fov, float nearClip, float farClip, float width, float height)
{
	this->position = intialPosition;

	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = roll;

	this->projectionMatrix = glm::perspective(glm::radians(fov), width / height, nearClip, farClip);
	this->nearClip = nearClip;
	this->farClip = farClip;
	this->fov = fov;

	this->viewMatrix = glm::translate(glm::mat4(1.f), intialPosition);

	this->cameraUp = glm::vec3(0.f, 1.f, 0.f);
	this->cameraFront = glm::vec3(0.f, 0.f, -1.f);
}

Camera::~Camera()
{
}

void Camera::update()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	direction.y = sin(glm::radians(this->pitch));
	this->cameraFront = glm::normalize(direction);

	this->viewMatrix = glm::lookAt(this->position, this->position + this->cameraFront, this->cameraUp);
}

void Camera::updateProjectionMatrix(float width, float height)
{
	this->projectionMatrix = glm::perspective(glm::radians(this->fov), width / height, this->nearClip, this->farClip);
}

glm::vec3& Camera::getCameraFront()
{
	return this->cameraFront;
}

glm::vec3& Camera::getCameraUp()
{
	return this->cameraUp;
}
