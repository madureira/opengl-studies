#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
private:
	GLFWwindow* m_Window;

public:
	Window(const char* title, int width, int height);
	~Window();
	bool isOpen();
	void clear();
	void update();
};
