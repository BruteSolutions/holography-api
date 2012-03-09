#include <iostream>
#include "structs.h"
#include "ColorTranslator.h"
#include "vec3.h"

using namespace std;

int main ( ){

	ColorVec3 factor = {1.0f,1.0f,1.0f};
	ColorTranslator ct = ColorTranslator(factor);
	ColorVec3 x = ct.getConversionFactor();
	cout << x.r << x.g << x.b << endl;
	return 0;
}
