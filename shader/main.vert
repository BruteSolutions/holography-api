#version 150

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 theColor;

uniform vec3 objectPos;
uniform vec3 camPos;
uniform mat4 worldPos;
uniform mat4 worldRotX;
uniform mat4 worldRotY;
uniform mat4 worldRotZ;
uniform mat4 objectRotX;
uniform mat4 objectRotY;
uniform mat4 objectRotZ;
uniform float scale;

smooth out vec4 color;

void main()
{

	color = theColor;
	vec4 position2 = objectRotX*objectRotY*objectRotZ*vec4(position.x*scale,(position.y-5)*scale,position.z*scale,position.w);
	gl_Position =vec4(0,5,0,0)+worldPos*(worldRotY*worldRotZ*worldRotX*vec4(position2.x + objectPos.x+camPos.x, position2.y + objectPos.y+camPos.y, position2.z + objectPos.z+camPos.z, position.w));
}
