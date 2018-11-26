#include "graphics/window.h"
#include "graphics/shader.h"

int main(void)
{
	int WINDOW_WIDTH = 640;
	int WINDOW_HEIGHT = 480;

	Window window("OpenGL Studies", WINDOW_WIDTH, WINDOW_HEIGHT, true);
	Shader shader("resources/shaders/basic.vsh", "resources/shaders/basic.fsh");

	GLfloat points[] = {
		 0.0f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	while (window.isOpen())
	{
		window.clear();

		shader.enable();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		window.update();
	}

	return 0;
}
