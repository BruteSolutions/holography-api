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
	//rotate object around its origin
	vec4 origin = vec4(0,5,0,0);
	position = objectRotX * objectRotY * objectRotZ * (position - origin);
	//scale object relative to origin
	position = scale*position;
	
	//move object camera might be removed (the camera should be fixed)
	position.x = position.x+objectPos.x+camPos.x;
	position.y = position.y+objectPos.y+camPos.y;
	position.z = position.z+objectPos.z+camPos.z;

	//rotate the world and and apply the frustum matrix (worldpos) add the origin
	gl_Position = origin + worldPos * worldRotX * worldRotY * worldRotZ * position;
}
