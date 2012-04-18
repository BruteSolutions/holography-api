#include <vector>

#include <glload/gl_3_3.h>
#include <GL/freeglut.h>

#include "Shared.h"
#include "GraphicalObject.h"
#include "ThreeDSpace.h"
#include "Scene.h"
#include <cstring>
#include <stdio.h>
#include <math.h>

Scene::Scene()
{
	cPos = {0,0,0};
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
	worldRotX.m[5]=1;
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
void Scene::selectNext(){
	threeDSpace->selectNext();
}
GraphicalObject * Scene::getNext(){ return threeDSpace->objects.at(0);}

std::vector<GraphicalObject*> Scene::getSelected(){
	return threeDSpace->selected;
}
GraphicalObject * Scene::getNextSelected(){;}
void Scene::deselectAll(){;}

void Scene::applyPos(GLuint shader)
{
	GLuint posLoc = glGetUniformLocation(shader, "worldPos");
    glUniformMatrix4fv(posLoc, 1, GL_FALSE, worldPos.m);

	GLuint posLoc2 = glGetUniformLocation(shader, "camPos");
    glUniform3f(posLoc2, cPos.x, cPos.y, cPos.z);

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
void Scene::setRotation(){
	worldRotX.m[5] = cos(angleX);
	worldRotX.m[6] = -sin(angleX);
	worldRotX.m[9] = sin(angleX);
	worldRotX.m[10] = cos(angleX); 

	worldRotY.m[0] = cos(angleY);
	worldRotY.m[2] = sin(angleY);
	worldRotY.m[8] = -sin(angleY);
	worldRotY.m[10] = cos(angleY); 

	worldRotZ.m[0] = cos(angleZ);
	worldRotZ.m[1] = -sin(angleZ);
	worldRotZ.m[4] = sin(angleZ);
	worldRotZ.m[5] = cos(angleZ); 
}

void Scene::translateCam(Vec3 trans)
{
  //TODO : make trans depend on the direction the camera is facing
	Vec4* transRel = matMult(trans);
	std::cout << "Transrel : " << transRel->x<<" "<<transRel->y <<" "<<transRel->z<<" "<< transRel->w<<"\n";
	
  Vec3 newPos = {cPos.x+transRel->x, cPos.y+transRel->y, cPos.z+transRel->z};
  cPos = newPos;
  std::cout << "campos:" <<cPos.x <<" " <<cPos.y<< " " << cPos.z<<"\n";

}

Vec4* Scene::matMult(Vec3 trans)
{
setRotation();
std::cout << "BEGIN MATMULT :" <<trans.x <<" " <<trans.y<< " " << trans.z<<"\n";
	Vec4 pos = {trans.x, trans.y,trans.z, 1};
	Vec4* res=new Vec4();
std::cout <<"ANGLES "<< angleX <<" " <<angleY << " " << angleZ <<"\n";
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			std::cout << worldRotX.m[i*4+j]<<" ";
}		std::cout <<"\n";}
std::cout <<"\n";
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			std::cout << worldRotY.m[i*4+j]<<" ";
}		std::cout <<"\n";}
std::cout <<"\n";
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			std::cout << worldRotZ.m[i*4+j]<<" ";
}		std::cout <<"\n";}

	for(int i = 0; i < 4; i++){
		float posCord;
		
		
		float r=0;
		for(int j = 0; j < 4; j++){
			if(j==0)
				posCord=pos.x;
			if(j==1)
				posCord=pos.y;
			if(j==2)
				posCord=pos.z;
			if(j==3)
			posCord=pos.w;
			r+=worldRotX.m[i*4+j]*posCord;
		}
		if(i==0)
			res->x=r;
		if(i==1)
			res->y=r;
		if(i==2)
			res->z=r;
		if(i==3)
			res->w=r;
		
	}

	for(int i = 0; i < 4; i++){
		float posCord;

		
		float r=0;
		for(int j = 0; j < 4; j++){
			if(j==0)
				posCord=res->x;
			if(j==1)
				posCord=res->y;
			if(j==2)
				posCord=res->z;
			if(j==3)
			posCord=res->w;
			r+=worldRotZ.m[i*4+j]*posCord;
		}
		if(i==0)
			res->x=r;
		if(i==1)
			res->y=r;
		if(i==2)
			res->z=r;
		if(i==3)
			res->w=r;
		
	}

	for(int i = 0; i < 4; i++){
		float posCord;

		
		float r=0;
		for(int j = 0; j < 4; j++){
			if(j==0)
				posCord=res->x;
			if(j==1)
				posCord=res->y;
			if(j==2)
				posCord=res->z;
			if(j==3)
			posCord=res->w;
			r+=worldRotY.m[i*4+j]*posCord;
		}
		if(i==0)
			res->x=r;
		if(i==1)
			res->y=r;
		if(i==2)
			res->z=r;
		if(i==3)
			res->w=r;
		
	}
	return res;
}
