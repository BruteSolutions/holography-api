#include <vector>

#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#include "Shared.h"
#include "GraphicalObject.h"
#include "ThreeDSpace.h"
#include "Scene.h"
#include <cstring>


/**
 * Scene constructor initiates all matrices.
 */
Scene::Scene() {
    cPos = {0, 0, 0};
    cDir = {1, 1, -1};
    fFrustumScale = 1.0f; fzNear = 1.0f; fzFar = 25.0f;
    memset(&worldPos.m, 0, sizeof(worldPos.m));
    memset(&worldRotX.m, 0, sizeof(worldRotX.m));
    memset(&worldRotY.m, 0, sizeof(worldRotY.m));
    memset(&worldRotZ.m, 0, sizeof(worldRotZ.m));
    
    worldPos.m[0] = fFrustumScale;
    worldPos.m[5] = fFrustumScale;
    worldPos.m[10] = (fzFar + fzNear)/(fzNear - fzFar);
    worldPos.m[14] = (2*fzFar*fzNear)/(fzNear - fzFar);
    worldPos.m[11] = -1.0f;
    angleX=0; 
    angleY=0;
    angleZ=0;
    memset(&rotationMatrix.m, 0, sizeof(rotationMatrix.m));
   
    rotationMatrix.m[0] = 1; rotationMatrix.m[5] = 1; rotationMatrix.m[ 10] = 1; rotationMatrix.m[15] = 1;

	backgroundHighlightning = false;
    threeDSpace = new ThreeDSpace();
}

/**
 * Returns the current 3D-space.
 * @return Current 3D-space.
 */
ThreeDSpace* Scene::get3DSpace() {
    return threeDSpace;
}

/**
 * Retrieves the current camera position.
 * @return Current camera position.
 */
Vec3 Scene::getCameraPosition() {
    return cPos;
}

/**
 * Selects the next item in 3D-space.
 */
void Scene::selectNext() {
    threeDSpace->selectNext();
}

/**
 * Retrieves the next object from 3D-space.
 * @return Retrieves the next GraphicalObject.
 */
GraphicalObject * Scene::getNext() {
    if(threeDSpace->objects.size() > 0 ){
        return threeDSpace->objects.at(0);
    }
    return NULL;
}

/**
 * Retrieves the current selection state.
 * @return Current selection state.
 */
std::vector<GraphicalObject*> Scene::getSelected() {
    return threeDSpace->selected;
}

/**
 * Retrieves the next selected object.
 * @return Retrieves the next selection object.
 */
GraphicalObject * Scene::getNextSelected() { ; }

/**
 * TODO.
 */
void Scene::deselectAll() { 
	threeDSpace->clearSelected(); 
}

/**
 * Merges a given scene to the current 3D-space.
 * @param scene Scene to merge.
 */
void Scene::merge(Scene *scene) {
    std::vector<GraphicalObject*> newObjects = scene->get3DSpace()->getObjects();
    for (std::vector<GraphicalObject*>::iterator it = newObjects.begin(); it != newObjects.end(); it++) {
        threeDSpace->addObject(*it);
    }
}

/**
 * Writes the current world and camera position and the world rotation.
 * @param shader program ID.
 */
void Scene::setUniforms(GLuint shader) {
    GLuint posLoc = glGetUniformLocation(shader, "worldPos");
    glUniformMatrix4fv(posLoc, 1, GL_FALSE, worldPos.m);

    GLuint posLoc2 = glGetUniformLocation(shader, "camPos");
    glUniform3f(posLoc2, cPos.x, cPos.y, cPos.z);

    GLuint rotLoc = glGetUniformLocation(shader, "worldRot");
    glUniformMatrix4fv(rotLoc, 1, GL_FALSE, rotationMatrix.m);

    GLuint scaleLoc = glGetUniformLocation(shader, "worldScale");
    glUniform1f(scaleLoc, threeDSpace->getScale());

    GLuint worldOriLoc = glGetUniformLocation(shader, "worldOrigin");
    glUniform3f(worldOriLoc, threeDSpace->origin.x,threeDSpace->origin.y,threeDSpace->origin.z);
}

/**
 * Translates camera.
 * @param trans Translation vector.
 */
void Scene::translateCam(Vec3 trans) {
    cPos = { cPos.x + trans.x, cPos.y + trans.y, cPos.z + trans.z };
}

/**
 *
 */
void Scene::autoRescale(){
	std::vector<GraphicalObject*> objects = get3DSpace()->getObjects();

	float avgX=0,avgY=0,avgZ = 0;
	float floats = 0;
	float max = 0.00001;
	for(int i = 0; i < objects.size(); i++){
//		float vertexData[objects.at(i)->getVertexDataSize()];
		GraphicalObject * object = objects.at(i);

		object->setPosition({0,0,0});
//		vertexData = objects.at(i)->getVertexData();
		floats += object->getVertexDataSize();
		for(int j = 0; j < object->getVertexDataSize(); j+=4){
			avgX += object->getVertexData()[j];
			avgY += object->getVertexData()[j+1];
			avgZ += object->getVertexData()[j+2];
		}
	}
	
	avgX /= floats;
	avgY /= floats;
	avgZ /= floats;
	for(int i = 0; i < objects.size(); i++){
		
		objects.at(i)->translate({-avgX,-avgY,-avgZ});
	}
	for(int i = 0; i < objects.size(); i++){
		//float * vertexData = (float *)objects.at(i)->getVertexData();
		GraphicalObject * object = objects.at(i);
		for(int j = 0; j < objects.at(i)->getVertexDataSize(); j++){
			if(j%4 == 3) continue;
			if(max < abs(object->getVertexData()[j])) max = abs(object->getVertexData()[j]);
		}
	}
	std::cout << "TJENA" << std::endl;
	get3DSpace()->setScale(5/max);
	cPos = { 0, 0, 0 };
	
}

/**
 * Rotate the x angle.
 * @param angle Angular adjustment.
 */

void Scene::rotateX(float angle) {
     
    Mat4 m;
    memset(&m.m, 0, sizeof(m));
    m.m[0] = 1; m.m[5] = 1; m.m[ 10] = 1; m.m[15] = 1;
m.m[5] = cos(angle);
m.m[6] = sin(angle);
m.m[9] = -sin(angle);
m.m[10] = cos(angle);

      rotationMatrix = Mat4::matrixMultiplication(m,rotationMatrix);
}

/**
 * Rotate the y angle.
 * @param angle Angular adjustment.
 */
void Scene::rotateY(float angle) {
    Mat4 m;//= { cos(angle), 0, -sin(angle), 0, 0, 1, 0, 0, sin(angle), 0, cos(angle), 0, 0, 0, 0, 1};
    memset(&m.m, 0, sizeof(m));
    m.m[0] = 1; m.m[5] = 1; m.m[ 10] = 1; m.m[15] = 1;
    m.m[0] = cos(angle);
    m.m[2] = -sin(angle);
    m.m[8] = sin(angle);
    m.m[10] = cos(angle); 

  rotationMatrix = Mat4::matrixMultiplication(m,rotationMatrix); 
}

/**
 * Rotate the z angle.
 * @param angle Angular adjustment.
 */
void Scene::rotateZ(float angle) {

    Mat4 m;// = { cos(angle), sin(angle), 0, 0, -sin(angle), cos(angle) , 0, 0, 0, 0, 1, 0, 0, 0 ,0 ,1};
    memset(&m.m, 0, sizeof(m));
    m.m[0] = 1; m.m[5] = 1; m.m[ 10] = 1; m.m[15] = 1;
    m.m[0] = cos(angle);
    m.m[1] = sin(angle);
    m.m[4] = -sin(angle);
    m.m[5] = cos(angle);  

  rotationMatrix = Mat4::matrixMultiplication(m,rotationMatrix);  
}

/**
 * Toggles background highlightning.
 */
void Scene::toggleBackgroundHighlightning() {
	backgroundHighlightning = !backgroundHighlightning;
}

/**
 * Gets the current state of background highlightning.
 */
bool Scene::getBackgroundHighlightning() {
	return backgroundHighlightning;
}
