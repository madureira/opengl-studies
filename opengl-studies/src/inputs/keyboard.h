#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../graphics/window.h"

class Keyboard
{
private:
	GLFWwindow* m_Window;

public:
	Keyboard(Window* window);

	bool isUpKeyPressed();
	bool isDownKeyPressed();
	bool isLeftKeyPressed();
	bool isRightKeyPressed();
	bool isWKeyPressed();
	bool isSKeyPressed();
	bool isAKeyPressed();
	bool isDKeyPressed();
};
