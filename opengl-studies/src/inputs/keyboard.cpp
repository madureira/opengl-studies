#include "keyboard.h"

Keyboard::Keyboard(Window* window):
	m_Window(window),
	m_Up(false),
	m_Down(false),
	m_Left(false),
	m_Right(false),
	m_W(false),
	m_S(false),
	m_A(false),
	m_D(false)
{
}

void Keyboard::captureEvents()
{
	this->resetState();

	if (this->isPressed(GLFW_KEY_UP))
	{
		this->m_Up = true;
	}

	if (this->isPressed(GLFW_KEY_DOWN))
	{
		this->m_Down = true;
	}

	if (this->isPressed(GLFW_KEY_LEFT))
	{
		this->m_Left = true;
	}

	if (this->isPressed(GLFW_KEY_RIGHT))
	{
		this->m_Right = true;
	}

	if (this->isPressed(GLFW_KEY_W))
	{
		this->m_W = true;
	}

	if (this->isPressed(GLFW_KEY_S))
	{
		this->m_S = true;
	}

	if (this->isPressed(GLFW_KEY_A))
	{
		this->m_A = true;
	}

	if (this->isPressed(GLFW_KEY_D))
	{
		this->m_D = true;
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

bool Keyboard::isWKeyPressed()
{
	return this->m_W;
}

bool Keyboard::isSKeyPressed()
{
	return this->m_S;
}

bool Keyboard::isAKeyPressed()
{
	return this->m_A;
}

bool Keyboard::isDKeyPressed()
{
	return this->m_D;
}

void Keyboard::resetState()
{
	this->m_Up = false;
	this->m_Down = false;
	this->m_Left = false;
	this->m_Right = false;
	this->m_W = false;
	this->m_S = false;
	this->m_A = false;
	this->m_D = false;
}

bool Keyboard::isPressed(int key)
{
	return glfwGetKey(this->m_Window->getGLFWwindow(), key);
}
