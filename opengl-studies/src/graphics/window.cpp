#include "window.h"

void window_resize(GLFWwindow *window, int width, int height);

Window::Window(const char* title, int width, int height)
{
	if (glfwInit())
	{
		this->m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (!this->m_Window)
		{
			glfwTerminate();
		}

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwMakeContextCurrent(this->m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetWindowPos(this->m_Window, (mode->width - width) / 2, (mode->height - height) / 2);
		glfwSetWindowSizeCallback(m_Window, window_resize);
		glfwSwapInterval(0);

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Could not initialize GLEW!" << std::endl;
		}
		else {
			std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
		}
	}
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::isOpen()
{
	return !glfwWindowShouldClose(this->m_Window);
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::update()
{
	glfwSwapBuffers(this->m_Window);
	glfwPollEvents();
}

void window_resize(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}
