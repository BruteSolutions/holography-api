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
    
    /*    
    worldRotX.m[0]=0.707106781;
    worldRotX.m[2]=-0.707106781;
    worldRotX.m[6]=1;
    worldRotX.m[9]=0.707106781;
    worldRotX.m[1]=0.707106781;
    worldRotX.m[15]=1;
    */

    worldRotX.m[0] = 1;
    worldRotX.m[5] = -1;
    worldRotX.m[10] = 1;
    worldRotX.m[15] = 1;    

    worldRotY.m[0] = 1;
    worldRotY.m[5] = 1;
    worldRotY.m[10] = 1;
    worldRotY.m[15] = 1;
    //worldRotY.m[1]=0.707106781;
    //worldRotY.m[15]=1;

    worldRotZ.m[0] = 1;
    worldRotZ.m[5] = 1;
    worldRotZ.m[10] = 1;
    worldRotZ.m[15] = 1;
    //worldRotZ.m[1]=0.707106781;
    //worldRotZ.m[15]=1;

    worldPos.m[0] = fFrustumScale;
    worldPos.m[5] = fFrustumScale;
    worldPos.m[10] = (fzFar + fzNear)/(fzNear - fzFar);
    worldPos.m[14] = (2*fzFar*fzNear)/(fzNear - fzFar);
    worldPos.m[11] = -1.0f;

    //worldPos.m[15]=1.0f;
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
    return threeDSpace->objects.at(0);
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
void Scene::deselectAll() { ; }

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
 * Writes the current world and camera position.
 * @param Shader program ID.
 */
void Scene::applyPos(GLuint shader) {
    GLuint posLoc = glGetUniformLocation(shader, "worldPos");
    glUniformMatrix4fv(posLoc, 1, GL_FALSE, worldPos.m);

    GLuint posLoc2 = glGetUniformLocation(shader, "camPos");
    glUniform3f(posLoc2, cPos.x, cPos.y, cPos.z);
}

/**
 * Applies the current rotation.
 * @param Shader program ID.
 */
void Scene::applyRot(GLuint shader) {
    GLuint posLocX = glGetUniformLocation(shader, "worldRotX");
    glUniformMatrix4fv(posLocX , 1, GL_FALSE, worldRotX.m);

    GLuint posLocY = glGetUniformLocation(shader, "worldRotY");
    glUniformMatrix4fv(posLocY , 1, GL_FALSE, worldRotY.m);

    GLuint posLocZ = glGetUniformLocation(shader, "worldRotZ");
    glUniformMatrix4fv(posLocZ , 1, GL_FALSE, worldRotZ.m);

    //Lägg på worldScale och worldOrigin, ändra på plats? eller sammla alla uniforms på samma ställe?

    GLuint scaleLoc = glGetUniformLocation(shader, "worldScale");
    glUniform1f(scaleLoc, threeDSpace->getScale());

    GLuint worldOriLoc = glGetUniformLocation(shader, "worldOrigin");
    glUniform3f(worldOriLoc, threeDSpace->origin.x,threeDSpace->origin.y,threeDSpace->origin.z);
}

/**
 * Updates the current world rotation matrix.
 */
void Scene::setRotation() {
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

/**
 * Translates camera.
 * @param trans Translation vector.
 */
void Scene::translateCam(Vec3 trans) {
    //TODO: make trans depend on the direction the camera is facing
    Vec4* transRel = matMult(trans);
//    std::cout << "Transrel : " << transRel->x << " " << transRel->y << " " << transRel-> z << " " << transRel-> w << "\n";

    Vec3 newPos = {cPos.x + transRel->x, cPos.y + transRel->y, cPos.z + transRel->z};
    cPos = newPos;
    //std::cout << "campos:" << cPos.x << " " << cPos.y << " " << cPos.z << "\n";
}

/**
 * Multiplies the current translation matrix.
 * @param trans Translation vector.
 * @return Returns the updated vector.
 */
Vec4* Scene::matMult(Vec3 trans) {
    Vec4 pos = {trans.x, trans.y, trans.z, 1};
    Vec4* res = new Vec4();

    for (int i = 0; i < 4; i++) {
        float posCord;
        
        float r = 0;
        for (int j = 0; j < 4; j++) {
            if (j == 0)
                posCord = pos.x;
            if (j == 1)
                posCord = pos.y;
            if (j == 2)
                posCord = pos.z;
            if (j == 3)
                posCord=pos.w;
            r += worldRotX.m[i*4 + j]*posCord;
        }
        
        if (i == 0)
            res->x = r;
        if (i == 1)
            res->y = r;
        if (i == 2)
            res->z = r;
        if (i == 3)
            res->w = r;
    }

    for (int i = 0; i < 4; i++) {
        float posCord;
        
        float r = 0;
        for (int j = 0; j < 4; j++) {
            if (j == 0)
                posCord = res->x;
            if (j == 1)
                posCord = res->y;
            if (j == 2)
                posCord = res->z;
            if (j == 3)
                posCord=res->w;
            r += worldRotY.m[i*4 + j]*posCord;
        }
        
        if (i == 0)
            res->x = r;
        if (i == 1)
            res->y = r;
        if (i == 2)
            res->z = r;
        if (i == 3)
            res->w = r;
    }
    return res;
}


/**
 * Rotate the x angle.
 * @param angle Angular adjustment.
 */
void Scene::rotateX(float angle) {
	angleX+=angle;
}

/**
 * Rotate the y angle.
 * @param angle Angular adjustment.
 */
void Scene::rotateY(float angle) {
	angleY+=angle;
}

/**
 * Rotate the z angle.
 * @param angle Angular adjustment.
 */
void Scene::rotateZ(float angle) {
	angleZ+=angle;
}

/**
 * Rotate the x angle.
 * @param angle Angular adjustment.
 */
void Scene::rotateXRad(float angle) {
	//TODO
}

/**
 * Rotate the y angle.
 * @param angle Angular adjustment.
 */
void Scene::rotateYRad(float angle) {
	//TODO
}

/**
 * Rotate the z angle.
 * @param angle Angular adjustment.
 */
void Scene::rotateZRad(float angle) {
	//TODO
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
