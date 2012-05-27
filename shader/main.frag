#version 150

smooth in vec4 color;
uniform vec3 factor;
//uniform float useHighlight;
uniform float highlight;

out vec4 outputColor;

void main()
{
	float r = factor.x * color.x;
	float g = factor.y * color.y;
	float b = factor.z * color.z;

 //vec3 processed = vec3(0,0, r+g+b);
  vec3 processed = vec3(r+g+b, 0.0f, 0.0f); //eftersom r+g+b kan max vara 1.0

  if(highlight == 1.0f) {
    processed.x = processed.x + 0.2f; //- processed.x;
  }

	outputColor.xyz = processed;
  outputColor.w = color.w;
//outputColor = color;
}
