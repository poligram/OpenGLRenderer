#pragma once
#include <vec3.hpp>
#include <mat4x4.hpp>

class Camera
{
public:
	Camera(glm::vec3 intialPosition, float pitch, float yaw, float roll, float fov, float nearClip, float farClip, float width, float height);
	~Camera();

	glm::vec3 position;
	float pitch, yaw, roll;
	glm::mat4 projectionMatrix;

	glm::mat4 viewMatrix;

	void update();
	void updateProjectionMatrix(float width, float height);

	glm::vec3& getCameraFront();
	glm::vec3& getCameraUp();

private:
	float fov;
	float nearClip;
	float farClip;
	glm::vec3 cameraUp;
	glm::vec3 cameraFront;
};

