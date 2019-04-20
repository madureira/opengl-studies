#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "graphics/window.h"
#include "graphics/shader.h"
#include "inputs/keyboard.h"

constexpr auto ONE_DEG_IN_RAD = (2.0 * 3.14159265358979323846) / 360.0; // 0.01744444;
constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 480;
constexpr bool V_SYNC = true;

int main()
{
	Window window("OpenGL Studies", WINDOW_WIDTH, WINDOW_HEIGHT, V_SYNC);
	Shader shader("resources/shaders/basic.vsh", "resources/shaders/basic.fsh");
	Keyboard keyboard(&window);

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

	float camSpeed = 1.0f; // 1 unit per second
	float camYawSpeed = 1.0f; // 10 degrees per second
	float camPos[3] = { 0.0f, 0.0f, 2.0f }; // don't start at zero, or we will be too close
	float camYaw = 0.0f; // y-rotation in degrees

	glm::mat4 T = glm::translate(glm::mat4(1.0), glm::vec3(-camPos[0], -camPos[1], -camPos[2]));
	glm::mat4 R = glm::rotate(glm::mat4(1.0), -camYaw, glm::vec3(-1.0f, 0.0f, 0.0f));
	glm::mat4 viewMat = R * T;

	float near = 0.1f; // clipping plane
	float far = 100.0f; // clipping plane
	float fov = 67.0f * ONE_DEG_IN_RAD; // convert 67 degrees to radians
	float aspect = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT; // aspect ratio

	// matrix components
	float range = tan(fov * 0.5f) * near;
	float Sx = (2.0f * near) / (range * aspect + range * aspect);
	float Sy = near / range;
	float Sz = -(far + near) / (far - near);
	float Pz = -(2.0f * far * near) / (far - near);

	float projMat[4 * 4] = {
		Sx,    0.0f,  0.0f,  0.0f,
		0.0f,  Sy,    0.0f,  0.0f,
		0.0f,  0.0f,  Sz,   -1.0f,
		0.0f,  0.0f,  Pz,    0.0f
	};

	int viewMatLocation = glGetUniformLocation(shader.getID(), "view");
	shader.enable();
	glUniformMatrix4fv(viewMatLocation, 1, GL_FALSE, glm::value_ptr(viewMat));

	int projMatLocation = glGetUniformLocation(shader.getID(), "proj");
	shader.enable();
	glUniformMatrix4fv(projMatLocation, 1, GL_FALSE, projMat);

	while (window.isOpen())
	{
		static double previousSeconds = glfwGetTime();
		double currentSeconds = glfwGetTime();
		double elapsedSeconds = currentSeconds - previousSeconds;
		previousSeconds = currentSeconds;
		bool isCamMoved = false;

		keyboard.captureEvents();

		if (keyboard.isAKeyPressed())
		{
			camPos[0] -= camSpeed * elapsedSeconds;
			isCamMoved = true;
		}

		if (keyboard.isDKeyPressed())
		{
			camPos[0] += camSpeed * elapsedSeconds;
			isCamMoved = true;
		}

		if (keyboard.isUpKeyPressed())
		{
			camPos[1] += camSpeed * elapsedSeconds;
			isCamMoved = true;
		}

		if (keyboard.isDownKeyPressed())
		{
			camPos[1] -= camSpeed * elapsedSeconds;
			isCamMoved = true;
		}

		if (keyboard.isWKeyPressed())
		{
			camPos[2] -= camSpeed * elapsedSeconds;
			isCamMoved = true;
		}

		if (keyboard.isSKeyPressed())
		{
			camPos[2] += camSpeed * elapsedSeconds;
			isCamMoved = true;
		}

		if (keyboard.isLeftKeyPressed())
		{
			camYaw += camYawSpeed * elapsedSeconds;
			isCamMoved = true;
		}

		if (keyboard.isRightKeyPressed())
		{
			camYaw -= camYawSpeed * elapsedSeconds;
			isCamMoved = true;
		}

		// update view matrix
		if (isCamMoved)
		{
			glm::mat4 T = glm::translate(glm::mat4(1.0), glm::vec3(-camPos[0], -camPos[1], -camPos[2]));
			glm::mat4 R = glm::rotate(glm::mat4(1.0), -camYaw, glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 view_mat = R * T;
			shader.enable();
			glUniformMatrix4fv(viewMatLocation, 1, GL_FALSE, glm::value_ptr(view_mat));
		}

		window.clear();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		window.render();
	}

	return 0;
}
