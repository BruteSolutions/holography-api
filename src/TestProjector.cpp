#include "TestProjector.h"

#include "Projector.h"
#include "Shared.h"

TestProjector::TestProjector()
{
}

void TestProjector::run()
{
  Vec3 pos = {0.5, 0.5, 0.5};
  Vec3 dir = {0.1, 0.2, 0.3};
  Projector p(NULL, 0, pos, dir);

  unsigned int prevShaderSize = p.getShaders().size();

  //try different methods, repeatedly
  for(int i = 0; i < 100; i++) {
    p.moveKeystoneCorner(i % 4, i % 2, 0.1);

    Vec3 newPos = {0.6, 0.5, 0.5};
    p.setPosition(newPos);
    if(  p.getPosition().x != newPos.x
      || p.getPosition().y != newPos.y
      || p.getPosition().z != newPos.z
    ) {
      throw(std::string("Error in handling of positions."));
    }
    p.setPosition(pos);

    Vec3 newDirection = {0.4, 0.3, 0.9};
    p.setDirection(newDirection);
    if(  p.getDirection().x != newDirection.x
      || p.getDirection().y != newDirection.y
      || p.getDirection().z != newDirection.z
    ) {
      throw(std::string("Error in handling of directions."));
    }
    p.setDirection(dir);

    if(p.getColorTranslator() == NULL) {
      throw(std::string("Error in handling of ColorTranslator."));
    }

    p.setConfiguration(p.getConfiguration());

    p.highlight();
    p.unHighlight();

    if(p.getShaders().size() != prevShaderSize) {
      throw(std::string("Error in handling of shaders."));
    }
  }
}
