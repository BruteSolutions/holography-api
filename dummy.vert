#version 330
layout 0 in vec4 position;
layout 1 in vec4 color;

uniform in vec3 factor;

out vec4 theColor;
void main()
{
	gl_Position = position;
	theColor = color;
}
