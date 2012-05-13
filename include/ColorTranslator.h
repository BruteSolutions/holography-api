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
    ColorTranslator() throw ( std::string );
    ColorTranslator( Vec3 factor ) throw ( std::string );
    ~ColorTranslator();
    void setConversionFactor( Vec3 factor ) throw ( std::string );
    Vec3 getConversionFactor() const;
    Shader* getShader() const;
    void setFactorUniform();
};

#endif
