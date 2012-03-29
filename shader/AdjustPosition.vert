#version 150

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 theColor;

uniform vec3 grObjPos;

smooth out vec4 color;

void main()
{
	color = theColor;
	gl_Position = position + vec4(grObjPos.x, 0.0f+grObjPos.y, 0.0f+grObjPos.z, 0.0f);
}
