#ifndef SCENE_H_
#define SCENE_H_

#include "Shader.h"
#include "Shared.h"
#include "ThreeDSpace.h"

class Scene {
public:
    Scene();
    ThreeDSpace * get3DSpace();        
    Vec3 getCameraPosition();
    void translateCam(Vec3 trans);

    ThreeDSpace * threeDSpace;
    Vec3 cPos, cDir;
    void selectNext();
    GraphicalObject * getNext();
    GraphicalObject * getNextSelected();
    void deselectAll();
    std::vector<GraphicalObject*> getSelected();
    Mat4 worldPos, worldRotX, worldRotY, worldRotZ;
    void applyPos(GLuint shader);
    float fFrustumScale ; float fzNear; float fzFar;
    void setUniforms(GLuint shader);
    void setRotation();
    float angleX, angleY,angleZ;
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void rotateXRad(float angle);
    void rotateYRad(float angle);
    void rotateZRad(float angle);
    void autoRescale();
    void merge(Scene * scene);
    void toggleBackgroundHighlightning();
    bool getBackgroundHighlightning();
private:        
    Mat4 rotationMatrix;
    bool backgroundHighlightning;
};

#endif
