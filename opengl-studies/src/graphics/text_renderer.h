#pragma once

#include <map>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "./shader.h"

struct Character {
	GLuint TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	GLuint Advance;
};

class TextRenderer
{
private:
	Shader* shader;
	std::map<GLchar, Character> Characters;
	GLuint VAO;
	GLuint VBO;
	std::string fontPath;

public:
	TextRenderer(std::string fontPath, int windowWidth, int windowHeight);

	void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
};
