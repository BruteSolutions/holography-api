#include <vector>

#include <glload/gl_3_3.h>
#include <GL/freeglut.h>

#include "Shared.h"
#include "GraphicalObject.h"
#include "ThreeDSpace.h"
#include "Scene.h"
#include <cstring>

Scene::Scene()
{
	cPos = {-1-1,1};
	cDir = {1,1,-1};
	 fFrustumScale = 1.0f ;  fzNear = 0.0f;  fzFar = 3.0f;
	memset(&worldPos.m, 0, sizeof(worldPos.m));
	memset(&worldRotX.m, 0, sizeof(worldRotX.m));
	memset(&worldRotY.m, 0, sizeof(worldRotY.m));
	memset(&worldRotZ.m, 0, sizeof(worldRotZ.m));
/*	
	worldRotX.m[0]=0.707106781;
	worldRotX.m[2]=-0.707106781;
	worldRotX.m[6]=1;
	worldRotX.m[9]=0.707106781;
	worldRotX.m[1]=0.707106781;
	worldRotX.m[15]=1;
*/

	worldRotX.m[0]=1;
	worldRotX.m[5]=-1;
	worldRotX.m[10]=1;
	worldRotX.m[15]=1;	

	worldRotY.m[0]=1;
	worldRotY.m[5]=1;
	worldRotY.m[10]=1;
	worldRotY.m[15]=1;
	//worldRotY.m[1]=0.707106781;
	//worldRotY.m[15]=1;

	worldRotZ.m[0]=1;
	worldRotZ.m[5]=1;
	worldRotZ.m[10]=1;
	worldRotZ.m[15]=1;
	//worldRotZ.m[1]=0.707106781;
//	worldRotZ.m[15]=1;

	worldPos.m[0]=fFrustumScale;
	worldPos.m[5]=fFrustumScale;
	worldPos.m[10]=(fzFar + fzNear)/(fzNear-fzFar);
	worldPos.m[14]=(2*fzFar*fzNear)/(fzNear-fzFar);
	worldPos.m[11]= -1.0f;

	
	//worldPos.m[15]=1.0f;

	threeDSpace = new ThreeDSpace();
}

ThreeDSpace* Scene::get3DSpace()
{
	return threeDSpace;
}

Vec3 Scene::getCameraPosition()
{
	return cPos;
}

void Scene::applyPos(GLuint shader)
{
	GLuint posLoc = glGetUniformLocation(shader, "worldPos");
    glUniformMatrix4fv(posLoc, 1, GL_FALSE, worldPos.m);

}

void Scene::applyRot(GLuint shader)
{

	GLuint posLocX = glGetUniformLocation(shader, "worldRotX");
    glUniformMatrix4fv(posLocX , 1, GL_FALSE, worldRotX.m);
	
	GLuint posLocY = glGetUniformLocation(shader, "worldRotY");
    glUniformMatrix4fv(posLocY , 1, GL_FALSE, worldRotY.m);

	GLuint posLocZ = glGetUniformLocation(shader, "worldRotZ");
    glUniformMatrix4fv(posLocZ , 1, GL_FALSE, worldRotZ.m);
}

