//#include <iostream>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <iostream>
#include "Shader.h"
#include "ColorTranslator.h"
#include "Shared.h"


ColorTranslator::ColorTranslator(){
	//Vec3 factor = {0.217f, 0.715f, 0.017f};
	Vec3 factor = {1.0f, 1.0f, 1.0f};
	setConversionFactor(factor);
	shader = new Shader("FragPosition.vert","redmonochrome.frag");
}
/* 
 * Constructor
 * @factor is an array of 3 floats. 
 */
ColorTranslator::ColorTranslator(Vec3 factor){
	setConversionFactor(factor);
    shader = new Shader("FragPosition.vert","redmonochrome.frag");
}
/*
 * Destroy constructor
 */
ColorTranslator::~ColorTranslator(){
    delete shader;
}
/*
 * Sets the factor of this class to the one sent in.
 * @factor is an array of 3 floats.
 */
void ColorTranslator::setConversionFactor(Vec3 factor){
    this->factor = factor;

}
/*
 * Returns a pointer to the factor of this class
 */
Vec3 ColorTranslator::getConversionFactor() const {
    return factor;
}
/*
 * Returns the pointer to the shader object specified (in case apply method isn't the right approach)
 */
Shader* ColorTranslator::getShader() {
	return shader; 
}
/*
 * Set the uniform "factor" so that the shader can access the factor.
 */
void ColorTranslator::apply()
{
    GLuint factorLocation = glGetUniformLocation(shader->getShaderProgram(), "factor");
    glUniform3f(factorLocation,factor.x, factor.y, factor.z);
}
