#include "./mouse.h"

static double x_off_set;
static double y_off_set;
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

Mouse::Mouse(Window* window)
{
	this->m_Window = window->getGLFWwindow();
	glfwSetInputMode(this->m_Window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
	glfwSetScrollCallback(this->m_Window, scroll_callback);
}

void Mouse::getCursorPosition(double* xPos, double* yPos)
{
	glfwGetCursorPos(this->m_Window, xPos, yPos);
}

void Mouse::getScrollOffSet(double* xOffSet, double* yOffSet)
{
	*xOffSet = x_off_set;
	*yOffSet = y_off_set;
	x_off_set = 0;
	y_off_set = 0;
}

bool Mouse::isLeftButtonPressed()
{
	return glfwGetMouseButton(this->m_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
}

bool Mouse::isRightButtonPressed()
{
	return glfwGetMouseButton(this->m_Window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	x_off_set = xoffset;
	y_off_set = yoffset;
}
