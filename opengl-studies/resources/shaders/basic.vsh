#version 400 core

// Vertex attributes for position and color
layout(location = 0) in vec2 in_position;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec4 in_color;

// uniform will contain the world matrix.
uniform mat3 screenTransform;

// output variables
out vec2 uv;
out vec4 color;

void main(void)
{
	//transform the vector
	vec3 transformed = screenTransform * vec3(in_position, 1);
	gl_Position = vec4(transformed, 1);

	// pass through uv and color
	uv = in_uv;
	color = in_color;
}
