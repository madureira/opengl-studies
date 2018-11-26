#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
private:
	GLFWwindow* m_Window;
	const char* m_Title;
	bool m_VSync;

public:
	Window(const char* title, int width, int height, bool vsync = false);
	~Window();
	bool isOpen();
	void clear();
	void update();

private:
	bool init();
	void updateFpsCounter();
};
