//#include <iostream>
//#include <GL/freeglut.h>
//#include "Shader.h"
#include "ColorTranslator.h"

ColorTranslator::ColorTranslator(float *factor){
		setConversionFactor(factor);
    //shader = Shader("","redmonochrome.frag");
}
ColorTranslator::~ColorTranslator(){
    delete factor;
}
void ColorTranslator::setConversionFactor(float *factor){
    this->factor = factor;
}
float* getConversionFactor(){
    return factor;
}
void apply(/* GLuint program */){
    //GLuint factorLocation = glGetUniformLocation(program, "factorLocation");
    //glUseProgram(program);
    //glUniform3f(factorLocation,factor[0],factor[1],factor[2]);
    //glUseProgram(0);
}
