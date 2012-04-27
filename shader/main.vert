#version 150

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 theColor;

uniform vec3 objectPos;
uniform vec3 camPos;
uniform vec3 objOrigin;
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
	vec4 position2 = objectRotY*objectRotZ*objectRotX*scale*vec4(position.x+objOrigin.x, position.y+objOrigin.y ,position.z+objOrigin.z,position.w/scale);
	gl_Position =vec4(-objOrigin.x,-objOrigin.y,-objOrigin.z, 0)+worldPos*(worldRotY*worldRotZ*worldRotX*vec4(position2.x + objectPos.x+camPos.x, position2.y + objectPos.y+camPos.y, position2.z + objectPos.z+camPos.z, position.w));
}

