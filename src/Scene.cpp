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
	float fFrustumScale = 1.0f ; float fzNear = 0.0f; float fzFar = 3.0f;
	memset(&worldPos.m, 0, sizeof(worldPos.m));
	worldPos.m[0]=fFrustumScale;
	worldPos.m[5]=fFrustumScale;
	worldPos.m[10]=1.0f;//(fzFar + fzNear)/(fzNear-fzFar);
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

void Scene::apply(GLuint shader)
{
	GLuint posLoc = glGetUniformLocation(shader, "worldPos");
    glUniformMatrix4fv(posLoc, 1, GL_FALSE, worldPos.m);
}
