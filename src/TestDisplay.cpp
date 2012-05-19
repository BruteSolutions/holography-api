#include "TestDisplay.h"
#include "Display.h"
#include "Projector.h"

TestDisplay::TestDisplay()
{
}

void TestDisplay::run()
{
  Display d;
  Projector p(NULL, 0);

  //try different methods, repeatedly
  for(int i = 0; i < 100; i++) {
    if(d.getProjectors()->size() != i) {
      throw(std::string("Invalid storage of Projectors"));
    }
    d.getMonitor();
    d.getColorTranslator();
    d.getBoundingCube();
    d.highlight();
    d.unHighlight();

    d.addProjector(&p);

    if(d.getConfigurations() == NULL) {
      throw(std::string("Invalid Configuration"));
    }
  }
}
