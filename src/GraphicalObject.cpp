#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <cstring>
#include <stdio.h>
#include <math.h>
#include "Scene.h"
#include "Shared.h"
#include "Matrix.h"
#include "GraphicalObject.h"

GraphicalObject::GraphicalObject() {
}

/**
 * GraphicalObject constructor
 * @param _vertexData Array containing the vertex data.
 * @param _vertexDataSize Should be the number of floats in _vertexData.
 * @param _colorData Array containing the color data for the object.
 * @param _colorDataSize Should be the number of floats in _colorData.
 * In most cases is _colorDataSize = _vertexDataSize.
 */
GraphicalObject::GraphicalObject(float _vertexData[], int _vertexDataSize, float _colorData[], int _colorDataSize) {	
	vertexData = _vertexData;
	colorData = _colorData;
	vertexDataSize = _vertexDataSize;
	colorDataSize = _colorDataSize;
	float avgX=0,avgY=0,avgZ=0;
/* calculate center of mass */
	for(int i=0;i<vertexDataSize;i+=4){
	    avgX += vertexData[i];
	    avgY += vertexData[i+1];
	    avgZ += vertexData[i+2];
	}

	avgX = avgX*4 / vertexDataSize;
	avgY = avgY*4 / vertexDataSize;
	avgZ = avgZ*4 / vertexDataSize;

	origin={avgX,avgY,avgZ};
	std::cout << "origin = " << avgX << ", " << avgY << ", " << avgZ << std::endl;
	highlight = false;

	mesh=0;
	memset(&pos, 0, 4*3);

	scale = 1;
	angleX = 0;
	angleY = 0;
	angleZ = 0;

    memset(&rotationMatrix.m, 0, sizeof(rotationMatrix.m));
    rotationMatrix.m[0] = 1; rotationMatrix.m[5] = 1; rotationMatrix.m[ 10] = 1; rotationMatrix.m[15] = 1;
}

/**
 * Returns the objects vertex data array.
 * @return Objects vertex data array.
 */
float* GraphicalObject::getVertexData() {	
	return vertexData;
}

/**
 * Returns the objects color data array.
 * @return Objects color data array.
 */
float* GraphicalObject::getColorData() {	
	return colorData;
}

/**
 * Sets a triangle at an index to the specified color
 * @param index is the index of the triangle to change color on
 * @param color is a 3 int vector taking a value between 0 255 for each component invalid values will be set to zero
 */
void GraphicalObject::setColorTriangle(int index, Vec3Int color){
	if(!(color.x >= 0 && color.x <= 255)){
		color.x = 0;
	}
	if(!(color.y >= 0 && color.y <= 255)){
	  color.y = 0;
	}
	if(!(color.z >= 0 && color.z <= 255)){
	  color.z = 0;
	}
	for(int i = 0, j = 0; i < colorDataSize; i+=4, j++){
		if(j == index){
      colorData[i] = color.x/255;
			colorData[i+1] = color.y/255;
			colorData[i+2] = color.z/255;
		}
	}
}
/**
 * Returns the color data vertex size.
 * @return Color data vertex size.
 */
int GraphicalObject::getVertexDataSize() {	
	return vertexDataSize;
}

/**
 * Returns the color data array size.
 * @return Color data array size.
 */
int GraphicalObject::getColorDataSize() {	
	return colorDataSize;
}
void GraphicalObject::setPosition(Vec3 newPos){
	pos = newPos;
}
/**
 * Draws the object.
 */
void GraphicalObject::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);

	glEnableVertexAttribArray(0);			
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);	
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject2);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	if(mesh)  
		glDrawArrays(GL_LINE_STRIP, 0, vertexDataSize/4);
	else
		glDrawArrays(GL_TRIANGLES, 0, vertexDataSize/4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

/**
 * Binds the buffer data of colarData and vertexData. 
 * Must be done before calling the method draw().
 */
void GraphicalObject::bindBufferData() {
	glGenBuffers(1, &positionBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, getVertexDataSize()*4, getVertexData(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);	

	glGenBuffers(1, &positionBufferObject2);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject2);
	glBufferData(GL_ARRAY_BUFFER, getColorDataSize()*4, getColorData(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glFlush();
}

/**
 * Calculates the rotation matrixes needed by the shader to rotate the object
 * based on the rotation variables angleX, angleY ,angleZ.
 */
void GraphicalObject::rotate() {
	/*objectRotX.m[5] = cos(angleX);
	objectRotX.m[6] = -sin(angleX);
	objectRotX.m[9] = sin(angleX);
	objectRotX.m[10] = cos(angleX); 

	objectRotY.m[0] = cos(angleY);
	objectRotY.m[2] = sin(angleY);
	objectRotY.m[8] = -sin(angleY);
	objectRotY.m[10] = cos(angleY); 

	objectRotZ.m[0] = cos(angleZ);
	objectRotZ.m[1] = -sin(angleZ);
	objectRotZ.m[4] = sin(angleZ);
	objectRotZ.m[5] = cos(angleZ); */

}

/**
 * Sets the highlight uniform so it can be accessed by the shader.
 * @param shader The shader that uses the highlight uniform.
 */
void GraphicalObject::setHighlightUniform(GLuint shader){
	GLuint highlightLoc = glGetUniformLocation(shader, "highlight");
    glUniform1f(highlightLoc, highlight);
}

/**
 * Sets the scale, objectRotX, objectRotY, objectRotZ and objOrigin 
 * uniforms so they can be accessed by the shader.
 * @param shader The shader that uses the scale, objectRotX, 
 * objectRotY, objectRotZ and objOrigin uniforms.
 */
void GraphicalObject::applyRotation(GLuint shader) {
	/*	
	for(int i = 0; i < 16; i++){
		printf("%f ",objectRotX.m[i]);
	}
	printf("\n");
	for(int i = 0; i < 16; i++){
		printf("%f ",objectRotY.m[i]);
	}
	printf("\n");
	for(int i = 0; i < 16; i++){
		printf("%f ",objectRotZ.m[i]);
	}
	printf("\n");*/
	//create a function that sets all uniforms instead
	GLuint scaleLoc = glGetUniformLocation(shader, "scale");
	glUniform1f(scaleLoc, scale);
	//std::cout << "\n\n"<<scale<<"\n\n";
    GLuint rotLoc = glGetUniformLocation(shader, "objectRot");
    glUniformMatrix4fv(rotLoc, 1, GL_FALSE, rotationMatrix.m);
/*
	GLuint posLocX = glGetUniformLocation(shader, "objectRotX");
    glUniformMatrix4fv(posLocX , 1, GL_FALSE, objectRotX.m);
	
	GLuint posLocY = glGetUniformLocation(shader, "objectRotY");
    glUniformMatrix4fv(posLocY , 1, GL_FALSE, objectRotY.m);

	GLuint posLocZ = glGetUniformLocation(shader, "objectRotZ");
    glUniformMatrix4fv(posLocZ , 1, GL_FALSE, objectRotZ.m);
*/
    GLuint originLoc = glGetUniformLocation(shader, "objOrigin");
    glUniform3f(originLoc, origin.x,origin.y,origin.z);
}

/**
 * Sets the highlight boolean.
 * @param _bool The new highlight value.
 */
void GraphicalObject::setHighlight(bool _bool) {
	highlight = _bool;
}

/**
 * Toggles the highligh boolean.
 * If highlight = TRUE before the call to toggleHighlight()
 * it will be FALSE after and vise versa.
 */
void GraphicalObject::toggleHighlight(){
	highlight = !highlight;
}

/**
 * Translates the object by the given offset by
 * updating the pos variable.
 * @param trans A Vec3 containing the offset values.
 */
void GraphicalObject::translate(Vec3 trans) {
	//std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
	pos = {pos.x+trans.x, pos.y+trans.y, pos.z+trans.z};
	origin = {origin.x+trans.x, origin.y+trans.y, origin.z+trans.z};
}

/**
 * Sets the objectPos uniform so it can be accessed by the shader.
 * @param shader The shader that uses the objectPos uniform.
 */
void GraphicalObject::applyTransformation(GLuint shader) {
    GLuint posLoc = glGetUniformLocation(shader, "objectPos");
    glUniform3f(posLoc, pos.x, pos.y, pos.z);
}

/**
 * Sets the origin for the object. 
 * The origin is the point in space which the object will rotate around.
 * @param ori The new origin value.
 */
void GraphicalObject::setOrigin(Vec3 ori) {
        origin = ori;
}
Vec3 GraphicalObject::getOrigin(){
	return origin;
}
/**
 * Checks if the object is meshed.
 * @return True if the object is meshed.
 * False otherwise.
 */
bool GraphicalObject::hasMesh() {
	return mesh;
}

/**
 * Sets mesh to TRUE or FALSE.
 * @param _mesh The new mesh boolean.
 */
void GraphicalObject::setMesh(bool _mesh) {
	mesh = _mesh;
}

/**
 * Scales the object by the provided factor.
 * @param factor The factor for scaling.
 */
void GraphicalObject::resize(double factor) {
	scale *= factor;
}

/**
 * Sets the scale of the object.
 * @param _scala The scale.
 */
void GraphicalObject::setScale(double _scale) {
	scale = _scale;
}

/**
 * Returns the scale of the object.
 * @return The scale.
 */
double GraphicalObject::getScale() {
	return scale;
}

/**
 * Increments the objects scale.
 * @param inc The increment.
 */
void GraphicalObject::incrementScale(double inc) {
	scale += inc;
}

/**
 * Tries to center the object around the given position. 
 * Relative to the cameras position.
 * Does not take rotation into account.
 * @param camPos The cameras offset.
 * @param optPos The point in space where the object will be centered around.
*/
void GraphicalObject::center(Vec3 camPos, Vec3 optPos)
{
	Vec3 finalOffset;
	for(int i=0; i<vertexDataSize; i+=4) {
		float x = vertexData[i], y = vertexData[i+1], z = vertexData[i+2], w = vertexData[i+3];
		finalOffset.x += optPos.x - (x + camPos.x);
		finalOffset.y += optPos.y - (y + camPos.y);
		finalOffset.z += optPos.z - (x + camPos.z);
	}
	finalOffset.x = finalOffset.x/(vertexDataSize/4);
	finalOffset.y = finalOffset.y/(vertexDataSize/4);
	finalOffset.z = finalOffset.z/(vertexDataSize/4);
	std::cout << "--------------------------------------------POS--"<<finalOffset.x<<finalOffset.y<<finalOffset.z <<" ---------------------------------------------" <<std::endl;
	pos = finalOffset;
}

void GraphicalObject::rotateX(float angle) {
     
    Mat4 m;
    memset(&m.m, 0, sizeof(m));
    m.m[0] = 1; m.m[5] = 1; m.m[ 10] = 1; m.m[15] = 1;
m.m[5] = cos(angle);
m.m[6] = sin(angle);
m.m[9] = -sin(angle);
m.m[10] = cos(angle);

    rotationMatrix = Mat4::matrixMultiplication(m, rotationMatrix);

    angleX+=angle;
}

/**
 * Rotate the y angle.
 * @param angle Angular adjustment.
 */
void GraphicalObject::rotateY(float angle) {
    Mat4 m;
    memset(&m.m, 0, sizeof(m));
    m.m[0] = 1; m.m[5] = 1; m.m[ 10] = 1; m.m[15] = 1;
    m.m[0] = cos(angle);
    m.m[2] = -sin(angle);
    m.m[8] = sin(angle);
    m.m[10] = cos(angle); 

    rotationMatrix = Mat4::matrixMultiplication(m, rotationMatrix);

    angleY+=angle;
}

/**
 * Rotate the z angle.
 * @param angle Angular adjustment.
 */
void GraphicalObject::rotateZ(float angle) {

    Mat4 m;
    memset(&m.m, 0, sizeof(m));
    m.m[0] = 1; m.m[5] = 1; m.m[ 10] = 1; m.m[15] = 1;
    m.m[0] = cos(angle);
    m.m[1] = sin(angle);
    m.m[4] = -sin(angle);
    m.m[5] = cos(angle);  

    rotationMatrix = Mat4::matrixMultiplication(m, rotationMatrix);

    angleZ+=angle;
}
/**
 * Rotates the object around the x axis.
 * @param angle The rotation angle in radians.
 */
void GraphicalObject::rotateXRad(float angle) {
	//TODO
}

/**
 * Rotates the object around the y axis.
 * @param angle The rotation angle in radians.
 */
void GraphicalObject::rotateYRad(float angle) {
	//TODO
}

/**
 * Rotates the object around the z axis.
 * @param angle The rotation angle in radians.
 */
void GraphicalObject::rotateZRad(float angle) {
	//TODO
}

