#version 330
in vec4 theColor;
uniform vec3 factor;
out vec4 outputColor;
void main()
{
	float r = factor.x * theColor.x 
	float g = factor.y * theColor.y 
	float b = factor.z * theColor.z;
	outputColor = vec4(r+g+b, 0.0f, 0.0f, theColor.w);

}
