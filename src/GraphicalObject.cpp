#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <cstring>
#include <stdio.h>
#include <math.h>
#include "Shared.h"
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
	origin={0,0,0};
	highlight = false;
	vertexDataSize = _vertexDataSize;
	colorDataSize = _colorDataSize;
	memset(&pos, 0, 4*3);
	memset(&objectRotX.m, 0, sizeof(objectRotX.m));
	memset(&objectRotY.m, 0, sizeof(objectRotY.m));
	memset(&objectRotZ.m, 0, sizeof(objectRotZ.m));
	objectRotX.m[0]=1;
	objectRotX.m[5]=1;
	objectRotX.m[10]=1;
	objectRotX.m[15]=1;	

	objectRotY.m[0]=1;
	objectRotY.m[5]=1;
	objectRotY.m[10]=1;
	objectRotY.m[15]=1;

	objectRotZ.m[0]=1;
	objectRotZ.m[5]=1;
	objectRotZ.m[10]=1;
	objectRotZ.m[15]=1;
	scale = 1;
	angleX = 0;
	angleY = 0;
	angleZ = 0;
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
	objectRotX.m[5] = cos(angleX);
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
	objectRotZ.m[5] = cos(angleZ); 

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
	GLuint posLocX = glGetUniformLocation(shader, "objectRotX");
    glUniformMatrix4fv(posLocX , 1, GL_FALSE, objectRotX.m);
	
	GLuint posLocY = glGetUniformLocation(shader, "objectRotY");
    glUniformMatrix4fv(posLocY , 1, GL_FALSE, objectRotY.m);

	GLuint posLocZ = glGetUniformLocation(shader, "objectRotZ");
    glUniformMatrix4fv(posLocZ , 1, GL_FALSE, objectRotZ.m);

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
	Vec3 newPos = {pos.x+trans.x, pos.y+trans.y, pos.z+trans.z};
	pos = newPos;
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

/**
 * Rotates the object around the x axis.
 * @param angle The rotation angle in degrees.
 */
void GraphicalObject::rotateX(float angle) {
	angleX+=angle;
}

/**
 * Rotates the object around the y axis.
 * @param angle The rotation angle in degrees.
 */
void GraphicalObject::rotateY(float angle) {
	angleY+=angle;
}

/**
 * Rotates the object around the z axis.
 * @param angle The rotation angle in degrees.
 */
void GraphicalObject::rotateZ(float angle) {
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

