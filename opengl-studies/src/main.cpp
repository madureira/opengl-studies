#include "graphics/window.h"
#include "graphics/shader.h"

int main(void)
{
	int WINDOW_WIDTH = 640;
	int WINDOW_HEIGHT = 480;

	Window window("OpenGL Studies", WINDOW_WIDTH, WINDOW_HEIGHT, true);
	Shader shader("resources/shaders/basic.vsh", "resources/shaders/basic.fsh");

	GLfloat points[3*3] = {
		 0.0f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	GLfloat colours[3*3] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	GLuint pointsVBO = 0;
	glGenBuffers(1, &pointsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	GLuint coloursVBO = 0;
	glGenBuffers(1, &coloursVBO);
	glBindBuffer(GL_ARRAY_BUFFER, coloursVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);

	GLuint VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, coloursVBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	// starts as an identity matrix
	float matrix[4*4] = {
		1.0f, 0.0f, 0.0f, 0.0f, // first column
		0.0f, 1.0f, 0.0f, 0.0f, // second column
		0.0f, 0.0f, 1.0f, 0.0f, // third column
		0.0f, 0.0f, 0.0f, 1.0f, // fourth column
	};
	
	int matrixLocation = glGetUniformLocation(shader.getID(), "matrix");
	shader.enable();
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, matrix);

	float speed = 1.0f; // move at 1 unit per second
	float lastPosition = 0.0f;

	while (window.isOpen())
	{
		static double previousSeconds = glfwGetTime();
		double currentSeconds = glfwGetTime();
		double elapsedSeconds = currentSeconds - previousSeconds;
		previousSeconds = currentSeconds;

		// reverse direction when going to far left or right
		if (fabs(lastPosition) > 1.0f)
		{
			speed = -speed;
		}

		// update the matrix
		matrix[12] = elapsedSeconds * speed + lastPosition;
		lastPosition = matrix[12];

		shader.enable();
		glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, matrix);

		window.clear();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		window.render();
	}

	return 0;
}
