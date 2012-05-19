#include "TestShader.h"
#include "Shader.h"

TestShader::TestShader()
{
}

void TestShader::run()
{
  Shader s("", "");

  //try different methods, repeatedly
  for(int i = 0; i < 100; i++) {
    s.getVertexShader();
    s.getFragmentShader();
    s.getShaderProgram();
    s.getParameters();
    s.addParameter("test", 0);
  }
}
