#include "window.h"

int g_gl_width;
int g_gl_height;
void window_resize(GLFWwindow *window, int width, int height);
void error_callback(int error, const char* description);

Window::Window(const char* title, int width, int height, bool vsync):
	m_Title(title),
	m_VSync(vsync),
	m_Window(nullptr)
{
	g_gl_width = width;
	g_gl_height = height;
	this->init();
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, g_gl_width, g_gl_height);
}

void Window::render()
{
	glfwSwapBuffers(this->m_Window);
	glfwPollEvents();
}

GLFWwindow* Window::getGLFWwindow()
{
	return this->m_Window;
}

int Window::getFpsCounter()
{
	static double previous_seconds = glfwGetTime();
	static int frame_count;
	double current_seconds = glfwGetTime();
	double elapsed_seconds = current_seconds - previous_seconds;
	static double fps = 0;

	if (elapsed_seconds > 0.25)
	{
		previous_seconds = current_seconds;
		fps = (double)frame_count / elapsed_seconds;
		//char tmp[128];
		//sprintf_s(tmp, "%s - opengl @ fps: %.2f", this->m_Title, fps);
		//glfwSetWindowTitle(this->m_Window, tmp);
		frame_count = 0;
	}

	frame_count++;

	return fps;
}

bool Window::init()
{
	if (!glfwInit())
	{
		std::cout << "Could not initialize GLFW!" << std::endl;
		return false;
	}

	this->m_Window = glfwCreateWindow(g_gl_width, g_gl_height, this->m_Title, NULL, NULL);
	if (!this->m_Window)
	{
		std::cout << "Could not create GLFWwindow*" << std::endl;
		glfwTerminate();
		return false;
	}

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwSetWindowPos(this->m_Window, (mode->width - g_gl_width) / 2, (mode->height - g_gl_height) / 2);
	glfwMakeContextCurrent(this->m_Window);
	glfwSetWindowUserPointer(m_Window, this);
	glfwSetWindowSizeCallback(m_Window, window_resize);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4); // Anti-Alising

	glfwSwapInterval(m_VSync ? 1 : 0);

	glfwSetErrorCallback(error_callback);

	// Initialize GLEW to setup the OpenGL Function pointers
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Could not initialize GLEW!" << std::endl;
		return false;
	}

	// Set OpenGL options
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_FRONT_FACE);
	glFrontFace(GL_CW);

	std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

	return true;
}

void window_resize(GLFWwindow *window, int width, int height)
{
	g_gl_width = width;
	g_gl_height = height;
	glViewport(0, 0, g_gl_width, g_gl_height);
}

void error_callback(int error, const char* description)
{
	std::cout << "GLFW ERROR: code " << error << " msg: " << description << std::endl;
}
