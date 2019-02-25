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

public:
	Keyboard(Window* window);

	void captureEvents();
	bool isUpKeyPressed();
	bool isDownKeyPressed();
	bool isLeftKeyPressed();
	bool isRightKeyPressed();

private:
	void resetState();
	bool isPressed(int key);
};
