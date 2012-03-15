//#include <iostream>
#include <GL/freeglut.h>
#include "Shader.h"
#include "ColorTranslator.h"

ColorTranslator::ColorTranslator(){
	float factor[3] = {0.217f, 0.715f, 0.017f};
	setConversionFactor(factor);
	shader = new Shader("","redmonochrome.frag");
}
/* 
 * Constructor
 * @factor is an array of 3 floats. 
 */
ColorTranslator::ColorTranslator(float *factor){
	setConversionFactor(factor);
    shader = new Shader("","redmonochrome.frag");
}
/*
 * Destroy constructor
 */
ColorTranslator::~ColorTranslator(){
    //delete factor;
    delete shader;
}
/*
 * Sets the factor of this class to the one sent in.
 * @factor is an array of 3 floats.
 */
void ColorTranslator::setConversionFactor(float *factor){
    this->factor = factor;
}
/*
 * Returns a pointer to the factor of this class
 */
float* ColorTranslator::getConversionFactor() const {
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
void apply( GLuint program ){
    //GLuint factorLocation = glGetUniformLocation(program, "factor");
    //glUseProgram(program); //I dont know what this does
    //glUniform3f(factorLocation,factor[0],factor[1],factor[2]);
    //glUseProgram(0); //I don't know what this does
}
