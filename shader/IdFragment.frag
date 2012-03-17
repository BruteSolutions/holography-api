#version 150

smooth in vec4 color;
uniform vec3 factor;

out vec4 outputColor;

void main()
{
	float r = factor.x * color.x / factor.x;
	float g = factor.y * color.y;
	float b = factor.z * color.z;

	outputColor = vec4(r, 0.0f, 0.0f, color.w);
}
