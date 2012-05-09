#ifndef __ColorTranslator_H
#define __ColorTranslator_H
#include <GL/freeglut.h>
#include "Shared.h"
#include "Shader.h"

//Class might be redundant as everything can be done with a shader

class ColorTranslator {
private:
    Vec3 factor;
    Shader * shader;
public:
    ColorTranslator();
    ColorTranslator(const ColorTranslator& copy);
    ColorTranslator(Vec3 factor);
    ~ColorTranslator();
    void setConversionFactor(Vec3 factor);
    Vec3 getConversionFactor() const;
    Shader* getShader();
    void apply( /*GLuint program*/ );
};

#endif
