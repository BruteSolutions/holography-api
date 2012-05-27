#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <vector>
#include "ColorTranslator.h"
#include "Scene.h"
#include "Monitor.h"
#include "Projector.h"
#include "UniversalConfiguration.h"

#ifndef DISPLAY_H_
#define DISPLAY_H_

class Display {
public:
    Display();
    void display(Scene scene);
    std::vector<Projector>* getProjectors();
    Monitor* getMonitor();
    ColorTranslator* getColorTranslator();
    void rebindBuffers(Scene *scene);
    void addProjector(Projector *projector);
    double getBoundingCube();
    void highlight();
    void unHighlight();
    void setConfigurations(UniversalConfiguration *uc);
    UniversalConfiguration * getConfigurations();
private:
    Monitor *monitor;
    std::vector<Projector> * projectorList;
    std::vector<Configuration> * configs;
    ColorTranslator *colorTranslator;
    int numProjectors;
    //final int WIDTH:
    //final int HEIGHT:
};

#endif
