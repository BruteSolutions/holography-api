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
uniform float worldScale;
uniform vec3 worldOrigin;




smooth out vec4 color;

void main()
{

	color = theColor;
	vec4 position2 = objectRotY*objectRotZ*objectRotX*((scale*vec4(position.x, position.y ,position.z,position.w/scale))+vec4(objOrigin.x,objOrigin.y,objOrigin.z,0));
	vec4 position3 =(vec4(-objOrigin.x,-objOrigin.y,-objOrigin.z, 0))+worldPos*(vec4(objectPos.x+camPos.x, objectPos.y+camPos.y, objectPos.z+camPos.z,0)+(worldRotY*worldRotZ*worldRotX*vec4(position2.x+worldOrigin.x, position2.y +worldOrigin.y, position2.z +worldOrigin.z, position.w)));
	gl_Position =worldScale*(vec4(position3.x,position3.y,position3.z,position3.w/worldScale)-vec4(worldOrigin.x,worldOrigin.y,worldOrigin.z,0));
}

