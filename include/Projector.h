#ifndef PROJECTOR_H_
#define PROJECTOR_H_

#include "ColorTranslator.h"

class Projector {
public:
    Projector(int * pointer, unsigned int len);
    Projector(int * pointer, unsigned int len, Vec3 pos, Vec3 dir);
    unsigned int getBufferSize();
    ColorTranslator * getColorTranslator();
    void setConfiguration(Configuration c);
    Configuration getConfiguration();
    void highlight();
    void unHighlight();
    int* getBuffer();
    void display(Scene scene);
    void addShader(Shader shader);
    std::vector<Shader> getShaders();
    Vec3 getPosition();
    Vec3 getDirection();
    void setPosition(Vec3 position);
    void setDirection(Vec3 direction_);

private:
    std::vector<Shader> shaders;
    int * pnt;
    unsigned int bufferSize;
    ColorTranslator * colorTranslator;
    Configuration configuration;
    bool highlighted;
    Vec3 pos;
    Vec3 direction;
};

#endif
