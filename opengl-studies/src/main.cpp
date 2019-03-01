#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "graphics/window.h"
#include "graphics/shader.h"
#include "inputs/keyboard.h"

#define ONE_DEG_IN_RAD (2.0 * 3.14159265358979323846) / 360.0 // 0.01744444

int main(void)
{
	int WINDOW_WIDTH = 640;
	int WINDOW_HEIGHT = 480;

	Window window("OpenGL Studies", WINDOW_WIDTH, WINDOW_HEIGHT, true);
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

	float cam_speed = 1.0f; // 1 unit per second
	float cam_yaw_speed = 1.0f; // 10 degrees per second
	float cam_pos[3] = { 0.0f, 0.0f, 2.0f }; // don't start at zero, or we will be too close
	float cam_yaw = 0.0f; // y-rotation in degrees

	glm::mat4 T = glm::translate(glm::mat4(1.0), glm::vec3(-cam_pos[0], -cam_pos[1], -cam_pos[2]));
	glm::mat4 R = glm::rotate(glm::mat4(1.0), -cam_yaw, glm::vec3(-1.0f, 0.0f, 0.0f));
	glm::mat4 view_mat = R * T;

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

	float proj_mat[4 * 4] = {
		Sx,    0.0f,  0.0f,  0.0f,
		0.0f,  Sy,    0.0f,  0.0f,
		0.0f,  0.0f,  Sz,   -1.0f,
		0.0f,  0.0f,  Pz,    0.0f
	};

	int view_mat_location = glGetUniformLocation(shader.getID(), "view");
	shader.enable();
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, glm::value_ptr(view_mat));
	int proj_mat_location = glGetUniformLocation(shader.getID(), "proj");
	shader.enable();
	glUniformMatrix4fv(proj_mat_location, 1, GL_FALSE, proj_mat);

	while (window.isOpen())
	{
		static double previousSeconds = glfwGetTime();
		double currentSeconds = glfwGetTime();
		double elapsed_seconds = currentSeconds - previousSeconds;
		previousSeconds = currentSeconds;
		bool cam_moved = false;

		keyboard.captureEvents();

		if (keyboard.isAKeyPressed())
		{
			cam_pos[0] -= cam_speed * elapsed_seconds;
			cam_moved = true;
		}

		if (keyboard.isDKeyPressed())
		{
			cam_pos[0] += cam_speed * elapsed_seconds;
			cam_moved = true;
		}

		if (keyboard.isUpKeyPressed())
		{
			cam_pos[1] += cam_speed * elapsed_seconds;
			cam_moved = true;
		}

		if (keyboard.isDownKeyPressed())
		{
			cam_pos[1] -= cam_speed * elapsed_seconds;
			cam_moved = true;
		}

		if (keyboard.isWKeyPressed())
		{
			cam_pos[2] -= cam_speed * elapsed_seconds;
			cam_moved = true;
		}

		if (keyboard.isSKeyPressed())
		{
			cam_pos[2] += cam_speed * elapsed_seconds;
			cam_moved = true;
		}

		if (keyboard.isLeftKeyPressed())
		{
			cam_yaw += cam_yaw_speed * elapsed_seconds;
			cam_moved = true;
		}

		if (keyboard.isRightKeyPressed())
		{
			cam_yaw -= cam_yaw_speed * elapsed_seconds;
			cam_moved = true;
		}

		// update view matrix
		if (cam_moved)
		{
			glm::mat4 T = glm::translate(glm::mat4(1.0), glm::vec3(-cam_pos[0], -cam_pos[1], -cam_pos[2]));
			glm::mat4 R = glm::rotate(glm::mat4(1.0), -cam_yaw, glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 view_mat = R * T;
			shader.enable();
			glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, glm::value_ptr(view_mat));
		}

		window.clear();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		window.render();
	}

	return 0;
}
