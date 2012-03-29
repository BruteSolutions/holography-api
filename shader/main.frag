#version 150

smooth in vec4 color;
uniform vec3 factor;
uniform float useHighlight;

out vec4 outputColor;

void main()
{
	float r = factor.x * color.x;
	float g = factor.y * color.y;
	float b = factor.z * color.z;

  vec3 processed = vec3((r+b+g)/3, 0.0f, 0.0f);

  if(useHighlight == 1.0f) {
    processed.x = 1.0f - processed.x;
  }

	outputColor.xyz = processed;
  outputColor.w = color.w;
}
