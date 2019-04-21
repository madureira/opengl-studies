#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../graphics/window.h"

class Mouse
{
private:
	GLFWwindow* m_Window;

public:
	Mouse(Window* window);

	void getCursorPosition(double* xPos, double* yPos);
	void getScrollOffSet(double* xOffSet, double* yOffSet);
	bool isLeftButtonPressed();
	bool isRightButtonPressed();
};
