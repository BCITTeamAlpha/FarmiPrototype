#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec3 normal;

out vec4 v_color;
out vec3 v_position;
out vec3 v_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	v_color = color;
	v_normal = normalize(normal);

	vec4 temp_position = view * model * vec4(position, 1.0);
	v_position = temp_position.xyz;
    gl_Position = projection * temp_position;
}