#include <vector>

#include <glload/gl_3_3.h>
#include <GL/freeglut.h>

#include "Shared.h"
#include "GraphicalObject.h"
#include "ThreeDSpace.h"
/**
 * ThreeDSpace constructor initiates important variables.
 */
ThreeDSpace::ThreeDSpace() {
    objects.reserve(10);
    Vec3 origin = {0, 0, 0};
    setOrigin(origin);
    current = 0;
    selected = std::vector<GraphicalObject*>(); 
    scale = 1;
}

/**
 * Returns a vector containing all the GraphicalObjects
 * currently in the ThreeDSpace.
 * @return Vector with all GraphicalObjects.
 */
std::vector<GraphicalObject*> ThreeDSpace::getObjects() {
    return objects;
}

/**
 * Adds an GraphicalObject to the ThreeDSpace.
 * @param object Graphical object  
 */
void ThreeDSpace::addObject(GraphicalObject * object) {
    objects.push_back(object);
}

/**
 * Sets the origin which all object in the ThreeDSpace 
 * will rotate around.
 * @param org New origin.
 */
void ThreeDSpace::setOrigin(Vec3 org) {
    origin = org;
}

/**
 * Returns the origin of the ThreeDSpace.
 * @return Origin of the ThreeDSpace.
 */
Vec3 ThreeDSpace::getOrigin() {
	return origin;
}

/**
 * Remove an GraphicalObject from the ThreeDSpace.
 * @param object Graphical object pointer
 */
void ThreeDSpace::removeObject(GraphicalObject * object) {
    std::cout << "removing... " << std::endl;
    int i = 0;
    std::cout << objects.size();
    for (std::vector<GraphicalObject*>::iterator it = objects.begin(); it != objects.end() ; it++) {
        if((*it) == object) {
            //vector::erase
            //iterator erase ( iterator position );
            std::cout << "equal " << i << std::endl;
            objects.erase(it);
            std::cout << "erase " << std::endl;
            return;

        }
        std::cout << i << std::endl;
        i++;
    }
}
/**
 * Selects the next GraphicalObject in the ThreeDSpace.
 */
void ThreeDSpace::selectNext() {
    selected.clear();
    if(objects.size() == 0) return;
    
    selected.push_back(objects.at(current));
    
    current++;
    if(current >= objects.size()) {
        current = 0;
    }
}
/**
 *
 */
void ThreeDSpace::clearSelected() {
   selected.clear();
}

/**
 * Binds buffer data for all the GraphicalObjects in the ThreeDSpace.
 */
void ThreeDSpace::bindBuffers() {
    for (std::vector<GraphicalObject*>::iterator it = objects.begin(); it != objects.end(); it++) {
        (*it)->bindBufferData();
    }
}

/**
 * Resize the ThreeDSpace.
 * @param factor The scaling factor.
 */
void ThreeDSpace::resize(double factor) {
    scale *= factor;
}

/**
 * Sets the scale for the ThreeDSpace.
 * @param _scale New scale.
 */
void ThreeDSpace::setScale(double _scale) {
    scale = _scale;
}

/**
 * Returns the scale of the ThreeDSpace.
 * @return The scale of the ThreeDSpace.
 */
double ThreeDSpace::getScale() {
    return scale;
}

/**
 * Increment the scale of the ThreeDSpace.
 * @param inc The increment.
 */
void ThreeDSpace::incrementScale(double inc) {

    scale += inc;
    std::cout << scale << std::endl;
}
