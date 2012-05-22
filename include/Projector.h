#ifndef PROJECTOR_H_
#define PROJECTOR_H_

#include <string.h>
#include "Configuration.h"
#include "ColorTranslator.h"
#include "Scene.h"

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
    int* getBuffer(); //not implemented
    void calcKeystone(GLuint pid) throw (std::string);
    void display(Scene scene);
    void addShader(Shader shader);
    std::vector<Shader> getShaders();
    Vec3 getPosition();
    Vec3 getDirection();
    void setPosition(Vec3 position);
    void setDirection(Vec3 direction_);
    void moveKeystoneCorner(int corner, int xory, float value);
    void setKeystoneObserved(KeystoneSetting f);
private:
    std::vector<Shader> shaders;
    int * pnt;
    unsigned int bufferSize;
    ColorTranslator * colorTranslator;
    Configuration configuration;
    bool highlighted;
    Vec3 pos;
    Vec3 direction;
    Mat4 keystone;
    float X1, X2,X3,X4, Y1,Y2,Y3,Y4;
};

#endif
