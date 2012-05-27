#ifndef ThreeDSpace_H_
#define ThreeDSpace_H_
#include <vector>
#include "GraphicalObject.h"

class ThreeDSpace
{
public:
    ThreeDSpace();
    std::vector<GraphicalObject*> getObjects();
    void addObject(GraphicalObject * object);
    void setOrigin(Vec3 org);
    Vec3 getOrigin();
    void bindBuffers();
    void selectNext();
    std::vector<GraphicalObject*> objects;
    Vec3 origin;
    void clearSelected();
    int current;
    std::vector<GraphicalObject*> selected;
    float scale;
    void removeObject(GraphicalObject*);
    void resize(double factor);
    void setScale(double _scale);
    double getScale();
    void incrementScale(double inc);
    void applyScale();
};

#endif
