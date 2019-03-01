#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../graphics/window.h"

class Keyboard
{
private:
	Window* m_Window;
	bool m_Up;
	bool m_Down;
	bool m_Left;
	bool m_Right;
	bool m_W;
	bool m_S;
	bool m_A;
	bool m_D;

public:
	Keyboard(Window* window);

	void captureEvents();
	bool isUpKeyPressed();
	bool isDownKeyPressed();
	bool isLeftKeyPressed();
	bool isRightKeyPressed();
	bool isWKeyPressed();
	bool isSKeyPressed();
	bool isAKeyPressed();
	bool isDKeyPressed();

private:
	void resetState();
	bool isPressed(int key);
};
