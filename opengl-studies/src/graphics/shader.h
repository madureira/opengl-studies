#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include "../utils/fileutils.h"

class Shader {
private:
	GLuint m_ShaderID;
	const char* m_VertPath;
	const char* m_FragPath;

public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	inline GLuint getID() {
		return m_ShaderID;
	}

	void enable() const;
	void disable() const;

private:
	GLint getUniformLocation(const GLchar* name);
	GLuint load();
};