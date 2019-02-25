#include "keyboard.h"

Keyboard::Keyboard(Window* window)
{
	this->m_Window = window;
	this->resetState();
}

void Keyboard::captureEvents()
{
	this->resetState();

	if (this->isPressed(GLFW_KEY_W) || this->isPressed(GLFW_KEY_UP))
	{
		this->m_Up = true;
	}

	if (this->isPressed(GLFW_KEY_S) || this->isPressed(GLFW_KEY_DOWN))
	{
		this->m_Down = true;
	}

	if (this->isPressed(GLFW_KEY_A) || this->isPressed(GLFW_KEY_LEFT))
	{
		this->m_Left = true;
	}

	if (this->isPressed(GLFW_KEY_D) || this->isPressed(GLFW_KEY_RIGHT))
	{
		this->m_Right = true;
	}
}

bool Keyboard::isUpKeyPressed()
{
	return this->m_Up;
}

bool Keyboard::isDownKeyPressed()
{
	return this->m_Down;
}

bool Keyboard::isLeftKeyPressed()
{
	return this->m_Left;
}

bool Keyboard::isRightKeyPressed()
{
	return this->m_Right;
}

void Keyboard::resetState()
{
	this->m_Up = false;
	this->m_Down = false;
	this->m_Left = false;
	this->m_Right = false;
}

bool Keyboard::isPressed(int key)
{
	return glfwGetKey(this->m_Window->getGLFWwindow(), key);
}
