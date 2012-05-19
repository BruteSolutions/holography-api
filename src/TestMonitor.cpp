#include "TestMonitor.h"

#include "Monitor.h"
#include "Shader.h"
#include "Shared.h"

TestMonitor::TestMonitor()
{
}

void TestMonitor::run()
{
  Monitor m;
  Shader s("main.vert", "main.frag");

  //try different methods, repeatedly
  for(int i = 0; i < 100; i++) {
    m.getProjector();

    if(m.getShaders().size() != i) {
      throw(std::string("Shaders not properly stored"));
    }

    m.addShader(s);
  }
}
