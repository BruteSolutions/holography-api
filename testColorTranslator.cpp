#include <iostream>
#include "ColorTranslator.h"
#include "Shader.h"
using namespace std;

int main ( ){

	float factor[3] = {1.0f,0.5f,1.0f};
	ColorTranslator ct = ColorTranslator(factor);
	float* x= ct.getConversionFactor();
	cout << x[0] << x[1] << x[2] << endl;
	Shader *s = ct.getShader();
	return 0;
}
