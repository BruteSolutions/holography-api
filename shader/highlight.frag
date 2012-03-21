#version 150

smooth in vec4 color;
out vec4 outputColor;

void main()
{
	outputColor = vec4(255 - color.x, 255 - color.y, 255 - color.z, color.w);
}
