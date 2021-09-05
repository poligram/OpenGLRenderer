#include "Application.h"
#include "Utilities/TextFileUtil.h"

#define INITIAL_WINDOW_SIZE_X 1080
#define INITIAL_WINDOW_SIZE_Y 720
#define WINDOW_TITLE "OpenGLRenderer"

int main()
{
	Application* app = new Application(INITIAL_WINDOW_SIZE_X, INITIAL_WINDOW_SIZE_Y, WINDOW_TITLE, false);
	app->startGameLoop();

	return 0;
}