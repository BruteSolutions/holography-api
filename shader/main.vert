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
uniform mat4 worldRot;
uniform mat4 objectRot;

smooth out vec4 color;

void main()
{
		
	
	color = theColor;
	
	vec4 position2 = position;
	
		//Move object to origin
	vec4 coordRelatedToOrigin = vec4(position.x, position.y ,position.z,position.w) - vec4(objOrigin.x,objOrigin.y,objOrigin.z,0) - vec4(worldOrigin.x, worldOrigin.y, worldOrigin.z, 0);
		//Rotate around origin
	//vec4 rotated;
	vec4 rotated = objectRot * coordRelatedToOrigin;	
	//vec4 rotated = objectRotY*objectRotZ*objectRotX*setOrigin;
		//Scale the object
	rotated = scale * vec4(rotated.x, rotated.y, rotated.z, 0);
	rotated.w = position.w;
		//Restore position
	position2 = rotated + vec4(objOrigin.x,objOrigin.y,objOrigin.z, 0)+ vec4(worldOrigin.x, worldOrigin.y, worldOrigin.z, 0);

	position2+= vec4(objectPos.x, objectPos.y, objectPos.z, 0) ;
	//position2 = coordRelatedToOrigin;

		//Set world origin
	position2 = vec4(position2.x, position2.y, position2.z, position.w) - vec4(worldOrigin.x, worldOrigin.y, worldOrigin.z, 0);
	
	//Add objectpos for nice world rotation world translation?	
			
	
		
	
		//Rotate
	position2 = worldRot * position2;
	//position2 = worldRotY*worldRotZ*worldRotX*position2;
		
		//Scale
	position2 = worldScale*vec4(position2.x, position2.y, position2.z, 0);
	position2.w = position.w;
		//Restore
	position2 += vec4(worldOrigin.x, worldOrigin.y, worldOrigin.z, 0);
	
		//Add translations
	position2 +=  vec4(camPos.x, camPos.y,camPos.z,0);
		
	
		//Perspective matrix	
	position2 = worldPos * position2;


		//Keystone
	position2 = keystone * position2;
	
	
	gl_Position = position2;
	
}

