#version 330
layout(location=1) in vec4 color;
uniform vec3 factor;
void main()
{
	float r = factor.x * color.x 
	float g = factor.y * color.y 
	float b = factor.z * color.z;
	gl_FragColor = vec4(r+g+b, 0.0f, 0.0f, color.w);
}
