#version 450 core

in layout(location = 0) dvec2 a_position;

uniform dmat2 u_model;
uniform dmat4 u_projection;
uniform vec2 u_renderOffset;

void main()
{
	gl_Position = vec4( u_projection * 
		dvec4(u_model * a_position + u_renderOffset, 0.0, 1.0) );
}