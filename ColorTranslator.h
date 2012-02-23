#ifndef __ColorTranslator_H
#define __ColorTranslator_H

#include "structs.h"
class Shader{};

class ColorTranslator{
private: 
	ColorVec3 factor;
	Shader shader;
public:
	ColorTranslator(ColorVec3 &factor);
	void setConversionFactor(ColorVec3 &factor);
	ColorVec3 &getConversationFactor(); 
	void apply(ColorVec4 color);
};
#endif
