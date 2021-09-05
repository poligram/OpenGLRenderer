#pragma once
#include <glad/glad.h>
#include <glfw3.h>

class Application
{
public:
	Application(int width, int height, const char* title, bool fullscreen);
	~Application();

	void startGameLoop();

	GLFWwindow*& getWindow();

private:
	GLFWwindow* window;
};

