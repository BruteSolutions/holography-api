#ifndef __ColorTranslator_H
#define __ColorTranslator_H
#include <GL/freeglut.h>
#include <string>
#include "Shared.h"
#include "Shader.h"

class ColorTranslator {
private:
    Vec3 factor;
    Shader * shader;
public:
    ColorTranslator() throws ( std::string );
    ColorTranslator( Vec3 factor ) throws ( std::string );
    ~ColorTranslator();
    void setConversionFactor( Vec3 factor ) throws ( std::string );
    Vec3 getConversionFactor() const;
    Shader* getShader();
    void setFactorUniform();
};

#endif
