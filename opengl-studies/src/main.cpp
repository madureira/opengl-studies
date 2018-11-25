#include "graphics/window.h"
#include "graphics/shader.h"

int main(void)
{
	int WINDOW_WIDTH = 640;
	int WINDOW_HEIGHT = 480;

	Window window("OpenGL Studies", WINDOW_WIDTH, WINDOW_HEIGHT);
	Shader shader("resources/shaders/basic.vsh", "resources/shaders/basic.fsh");

	while (window.isOpen())
	{
		window.clear();

		window.update();
	}

	return 0;
}