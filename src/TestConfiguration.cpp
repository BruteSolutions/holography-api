#include <fstream>

#include "TestConfiguration.h"
#include "Configuration.h"

#include "Shared.h"

TestConfiguration::TestConfiguration()
{
  of.open("tmp");
}

void TestConfiguration::run()
{

  Vec3 v = {0.1, 0.1, 0.1};
  Configuration c(v, v, v);

  //try different methods, repeatedly
  for(int i = 0; i < 100; i++) {
    c.getPosition();
    c.getDirection();
    c.getColorTranslatorFactor();
    c.writeToStream(of);
  }
}
