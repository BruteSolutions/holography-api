#version 150

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 theColor;

uniform vec3 objectPos;

smooth out vec4 color;

void main()
{
	color = theColor;
	gl_Position = vec4(position.x + objectPos.x, position.y + objectPos.y, position.z + objectPos.z, position.w);
}
