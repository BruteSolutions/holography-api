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
uniform mat4 keystone;
uniform float scale;
uniform float worldScale;
uniform vec3 worldOrigin;

smooth out vec4 color;

void main()
{

	color = theColor;
	
	vec4 position2 = vec4(0,0,0,0);
	
		//Move object to origin
	vec4 setOrigin = vec4(position.x, position.y ,position.z,position.w) + vec4(objOrigin.x,objOrigin.y,objOrigin.z,0);
		//Rotate around origin
	vec4 rotated = objectRotY*objectRotZ*objectRotX*setOrigin;
		//Restore position
	position2 = rotated - vec4(objOrigin.x,objOrigin.y,objOrigin.z, 0);
		//Scale the object
	position2 = scale * vec4(position2.x, position2.y, position2.z, position2.w/scale);
	

		//Set world origin
	position2 = vec4(position2.x, position2.y, position2.z, position.w) + vec4(worldOrigin.x, worldOrigin.y, worldOrigin.z, 0);
	
	
	
	
		//Rotate
	position2 = worldRotY*worldRotZ*worldRotX*position2;
		//Restore
	position2 -= vec4(worldOrigin.x, worldOrigin.y, worldOrigin.z, 0);
	
		//Add translations
	position2 +=  vec4(camPos.x, camPos.y,camPos.z,0);
	//Add objectpos for nice world rotation
	
	position2+= vec4(objectPos.x, objectPos.y, objectPos.z, 0);
	
		//Perspective matrix	
	position2 = worldPos * position2;
		//Scale
	position2 = worldScale*vec4(position2.x, position2.y, position2.z, position2.w/worldScale);

	gl_Position = keystone * position2;
}

