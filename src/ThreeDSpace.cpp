#include <vector>

#include <glload/gl_3_3.h>
#include <GL/freeglut.h>

#include "Shared.h"
#include "GraphicalObject.h"
#include "ThreeDSpace.h"

ThreeDSpace::ThreeDSpace() {
    objects.reserve(10);
    Vec3 origin = {0, 0, 0};
    setOrigin(origin);
    current = 0;
    selected = std::vector<GraphicalObject*>(); 
    scale = 1;
}

std::vector<GraphicalObject*> ThreeDSpace::getObjects() {
    return objects;
}

void ThreeDSpace::addObject(GraphicalObject * object) {
    objects.push_back(object);
}

void ThreeDSpace::setOrigin(Vec3 org) {
    origin = org;
}

Vec3 ThreeDSpace::getOrigin() {
	return origin;
}

void ThreeDSpace::selectNext() {
    selected.clear();
    selected.push_back(objects.at(current));
    current++;
    if(current >= objects.size()) {
        current = 0;
    }
}

void ThreeDSpace::bindBuffers() {
    for (std::vector<GraphicalObject*>::iterator it = objects.begin(); it != objects.end(); it++) {
        (*it)->bindBufferData();
    }
}

void ThreeDSpace::resize(double factor) {
    scale *= factor;
}

void ThreeDSpace::setScale(double _scale) {
    scale = _scale;
}

double ThreeDSpace::getScale() {
    return scale;
}

void ThreeDSpace::incrementScale(double inc) {
    scale += inc;
}
