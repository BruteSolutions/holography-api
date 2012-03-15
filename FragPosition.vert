#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 theColor;

smooth out vec4 color;

void main()
{
	color = theColor;
	gl_Position = position;
}
