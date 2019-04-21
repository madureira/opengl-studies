#include "keyboard.h"

Keyboard::Keyboard(Window* window)
{
	this->m_Window = window->getGLFWwindow();
}

bool Keyboard::isUpKeyPressed()
{
	return glfwGetKey(this->m_Window, GLFW_KEY_UP);
}

bool Keyboard::isDownKeyPressed()
{
	return glfwGetKey(this->m_Window, GLFW_KEY_DOWN);
}

bool Keyboard::isLeftKeyPressed()
{
	return glfwGetKey(this->m_Window, GLFW_KEY_LEFT);
}

bool Keyboard::isRightKeyPressed()
{
	return glfwGetKey(this->m_Window, GLFW_KEY_RIGHT);
}

bool Keyboard::isWKeyPressed()
{
	return glfwGetKey(this->m_Window, GLFW_KEY_W);
}

bool Keyboard::isSKeyPressed()
{
	return glfwGetKey(this->m_Window, GLFW_KEY_S);
}

bool Keyboard::isAKeyPressed()
{
	return glfwGetKey(this->m_Window, GLFW_KEY_A);
}

bool Keyboard::isDKeyPressed()
{
	return glfwGetKey(this->m_Window, GLFW_KEY_D);
}
