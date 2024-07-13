#version 450 core

in layout(location = 0) vec2 a_position;

uniform mat4 u_projection;

void main()
{
	gl_Position = u_projection * vec4(a_position.xy, 0.0, 1.0);
}