#ifndef __ColorTranslator_H
#define __ColorTranslator_H
#include "structs.h"
//Class might be redundant as everything can be done with a shader
class Shader{};

class ColorTranslator{
private: 
	ColorVec3 factor;
	Shader shader;
public:
	ColorTranslator(ColorVec3 factor){
		setConversionFactor(factor);
//		this->shader = NULL; //Shader("","redmonochrome.frag");
	}

	void setConversionFactor(ColorVec3 factor){
		this->factor = factor;
	}
	ColorVec3 &getConversionFactor(){
		return factor;
	} 
	void apply(float * colors, int size){ //Get whole color buffer for colors, apply factor
		for(int i = 0; i < size; i=i+4){
				colors[i]=colors[i]*factor.r;		//r
				colors[i+1]=colors[i+1]*factor.g;	//g
				colors[i+2]=colors[i+2]*factor.b;	//b
													//w
		}		
	}
};
#endif
