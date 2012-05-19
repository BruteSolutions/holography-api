#include <iostream>
#include <list>
#include <cstdlib>
#include <string>

#include <glload/gl_3_3.h>

#include "Shared.h"
#include "Shader.h"
#include "GraphicalObject.h"
#include "ThreeDSpace.h"
#include "Scene.h"
#include "ColorTranslator.h"
#include "Projector.h"
#include "Display.h"

#include "TestCase.h"
#include "TestFramework.h"
#include "TestShader.h"
#include "TestColorTranslator.h"
#include "TestConfiguration.h"

#include <GL/glut.h>

int main()
{
  TestFramework framework;

  framework.addTestCase(new TestShader());
  framework.addTestCase(new TestColorTranslator());
  framework.addTestCase(new TestConfiguration());

  if(framework.test()) {
    std::cout << "All tests passed" << std::endl;
  }
  else {
    std::cerr << "Some test failed" << std::endl;
  }
  return(0);
}
