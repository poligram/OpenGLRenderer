#include "Application.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Shader/AShader/Shader.h"
#include "Model/Model.h"

#include "Camera/Camera.h"

Camera camera(glm::vec3(0.f, 0.f, -3.f), 0.f, -90.f, 0.f, 75.f, 0.1f, 100.f, 1080.f, 720.f);

float lastX = 1080.f/2.f;
float lastY = 720.f/2.f;
float deltaTime = 0.f;

std::vector<glm::vec3> vertices = {
	glm::vec3(-0.5f,-0.5f,0.f),
	glm::vec3(0.5f,-0.5f,0.f),
	glm::vec3(0.f,0.5f,0.f)
};

std::vector<unsigned int> indices = {
	0,1,2
};

std::vector<glm::vec2> texCoords = {
	glm::vec2(1.f,0.f),
	glm::vec2(0.f,1.f),
	glm::vec2(1.f,1.f),
};

void framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	camera.updateProjectionMatrix(width, height);
}

void keyboardCallback(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	float speed = 2.f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 4.f * deltaTime;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.position += speed * camera.getCameraFront();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.position -= speed * camera.getCameraFront();
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.position -= speed * glm::normalize(glm::cross(camera.getCameraFront(),camera.getCameraUp()));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.position += speed * glm::normalize(glm::cross(camera.getCameraFront(), camera.getCameraUp()));
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera.position += speed * camera.getCameraUp();
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		camera.position -= speed * camera.getCameraUp();
	}
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	camera.yaw += xOffset;
	camera.pitch += yOffset;

	if (camera.pitch > 89.0f)
	{
		camera.pitch = 89.0f;
	}
	else if (camera.pitch < -89.0f)
	{
		camera.pitch = -89.0f;
	}
}

Application::Application(int width, int height, const char* title, bool fullscreen)
{
	if (glfwInit() == GLFW_FALSE)
	{
		printf("ERROR: glfwInit() == GLFW_FALSE\n");
		exit(-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		printf("ERROR: glfwCreateWindow == NULL\n");
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("ERROR: gladLoadGLLoader = false\n");
		glfwTerminate();
		glfwDestroyWindow(window);
		exit(-1);
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
	glfwSetCursorPosCallback(window, mouseCallback);

	this->window = window;
}

Application::~Application()
{
	glfwTerminate();
	glfwDestroyWindow(this->window);
}

void Application::startGameLoop()
{

	Shader* shader = new Shader("Shaders/BasicVertexShader.vs", "Shaders/BasicFragmentShader.fs");

	Mesh mesh;
	mesh.vertices = vertices;
	mesh.indices = indices;
	mesh.texCoords = texCoords;
	mesh.normals.push_back(glm::vec3(0.f, 0.f, 0.f));

	Model model(mesh, false);

	float startTime = 0.f;

	while (!glfwWindowShouldClose(this->window))
	{
		startTime = glfwGetTime();

		//Process Events
		keyboardCallback(window);

		//Render
		glClearColor(0.1f, 0.5f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader->useProgram();

		glm::mat4 modelMatrix = glm::mat4(1.f);
		modelMatrix = glm::rotate(modelMatrix, glm::radians(55.f), glm::vec3(1.f, 0.f, 0.f));

		camera.update();

		shader->setUniformMat4("modelMatrix", modelMatrix);
		shader->setUniformMat4("viewMatrix", camera.viewMatrix);
		shader->setUniformMat4("projectionMatrix", camera.projectionMatrix);

		model.bindVAO();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.getEBO());
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		glfwSwapBuffers(this->window);
		glfwPollEvents();

		deltaTime = glfwGetTime() - startTime;
	}
}

GLFWwindow*& Application::getWindow()
{
	return this->window;
}
