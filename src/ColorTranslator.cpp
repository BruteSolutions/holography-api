//#include <iostream>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <string>
#include <iostream>
#include "Shader.h"
#include "ColorTranslator.h"
#include "Shared.h"


/*
 * Constructs a new ColorTranslator with a standard conversion factor.
 */
ColorTranslator::ColorTranslator() throw ( std::string ) {
    Vec3 factor = { 0.217f, 0.715f, 0.017f };
    setConversionFactor( factor );
    shader = new Shader( "main.vert","main.frag" );
}

/*
 * Constructs a new ColorTranslator with the given conversion factor.
 * @param factor a vector of 3 floats that determine the amount of red, green 
 * that will be converted to red. 
 */
ColorTranslator::ColorTranslator( Vec3 factor ) throw ( std::string ) {
    setConversionFactor( factor );
    shader = new Shader( "main.vert","main.frag" );
}

/*
 * Destructor.
 */
ColorTranslator::~ColorTranslator() {
    delete shader;
}

/*
 * Sets the factor of this class.
 * If the sum of the components in factor is bigger than 1 normalize the components.
 * @param factor a vector of 3 floats that determine the amount of red, green 
 * that will be converted to red.
 */
void ColorTranslator::setConversionFactor( Vec3 factor ) throw ( std::string ) {
    if (factor.x < 0)
    	throw std::string("IllegalArgumentException(The first conversion-factor is less than 0.)");
	if (factor.y < 0)
		throw std::string("IllegalArgumentException(The second conversion-factor is less than 0.)");
	if (factor.z < 0)
		throw std::string("IllegalArgumentException(The third conversion-factor is less than 0.)");
    float factorSum = factor.x + factor.y + factor.z;
    if( factorSum > 1 ){ //normalize components so that the sum will be one
    	factor.x = factor.x / factorSum;
        factor.y = factor.y / factorSum;
        factor.z = factor.z / factorSum;
    }
    this->factor = factor;
}

/*
 * Returns a pointer to the factor of this class
 * @return the factor of this class.
 */
Vec3 ColorTranslator::getConversionFactor() const 
{
    return factor;
}

/*
 * Returns the pointer to the shader object specified (in case apply method isn't the right approach)
 * @return a pointer to the shader object of this class.
 */
Shader* ColorTranslator::getShader() const {
    return shader; 
}

/*
 * Sets the uniform "factor" so that the fragment shader can access the factor of this class.
 */
void ColorTranslator::setFactorUniform() {
    GLuint factorLocation = glGetUniformLocation( shader->getShaderProgram(), "factor" );
    glUniform3f( factorLocation, factor.x, factor.y, factor.z );
}
