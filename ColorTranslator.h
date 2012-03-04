#ifndef __ColorTranslator_H
#define __ColorTranslator_H
//#include <string>
//#include "structs.h"

//Class might be redundant as everything can be done with a shader
class Shader{};

class ColorTranslator{
private: 
    float *factor;
    Shader shader;
public:
	  ColorTranslator(float *factor);
    ~ColorTranslator();
	  void setConversionFactor(float *factor);
	  float* getConversionFactor();
    void apply(/* GLuint program */);
};
#endif
