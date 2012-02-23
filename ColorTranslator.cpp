#include "structs.h"

ColorTranslator::ColorTranslator(ColorVec3 &factor){
	setConversionfactor(factor);
	shader = NULL;
}
void ColorTranslator::setConversionFactor(ColorVec3 &factor){
	this.factor = factor;
}
ColorVec3 &ColorTranslator::getConversationFactor(){
	return factor;
}
void ColorTranslator::apply(ColorVec4 color){
	
}

