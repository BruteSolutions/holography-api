#ifndef __ColorTranslator_H
#define __ColorTranslator_H
#include <string>
#include "structs.h"

//Class might be redundant as everything can be done with a shader
class Shader{};

class ColorTranslator{
private: 
    float *factor;
    std::string redmonochromeShader (
        "#version 330\n"
	      "in vec4 inColor;\n"
	      "uniform vec3 factor;\n"
	      "out vec4 outColor;\n"
	      "void main()\n"
	      "{\n"
	      " float r = inColor.x*factor.x;\n"
	      " float g = inColor.y*factor.y;\n"
	      " float b = inColor.z*factor.z;\n"
	      " outColor = vec4( r + g + b, 0.0f, 0.0f, 1.0f);\n"
	      "}\n"
    );
	  Shader shader;
public:
	  ColorTranslator(float *factor){
		    setConversionFactor(factor);
	  }
    ~ColorTranslator(){
        delete factor;
    }
	  void setConversionFactor(float *factor){
		    this->factor = factor;
	  }
	  float* getConversionFactor(){
		    return factor;
	  }
/* redundant method?
   void apply(float * colors, int size){ 
	  //Get whole color buffer for colors, apply factor
		    for(int i = 0; i < size; i=i+4){
				    colors[i]=colors[i]*factor.r;		//r
				    colors[i+1]=colors[i+1]*factor.g;	//g
				    colors[i+2]=colors[i+2]*factor.b;	//b
													//w
		    }
	  }*/
};
#endif
