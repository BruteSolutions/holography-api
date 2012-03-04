#version 330
in vec4 theColor;
uniform vec3 factor;

void main()
{
	color = factor.x * theColor.x + factor.y * theColor.y + factor.z*theColor.z;
	gl_Color = vec4(color, 0.0f, 0.0f, theColor.w);

}
