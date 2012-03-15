#ifndef __ColorTranslator_H
#define __ColorTranslator_H
#include <GL/freeglut.h>
#include "Shader.h"

//Class might be redundant as everything can be done with a shader

class ColorTranslator{
private: 
    float *factor;
    Shader shader;
public:
	ColorTranslator();
	ColorTranslator(const ColorTranslator& copy);
	ColorTranslator(float *factor);
    ~ColorTranslator();
	void setConversionFactor(float *factor);
	float* getConversionFactor() const;
	Shader* getShader() ;
    void apply( GLuint program );
};
#endif
