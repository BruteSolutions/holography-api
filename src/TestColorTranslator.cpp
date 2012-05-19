#include "TestColorTranslator.h"
#include "ColorTranslator.h"

#include "Shared.h"

TestColorTranslator::TestColorTranslator()
{
}

void TestColorTranslator::run()
{
  ColorTranslator c;

  //try different methods, repeatedly
  for(int i = 0; i < 100; i++) {
    Vec3 v = {0.2, 0.3, 0.4};
    c.setConversionFactor(v);
    c.getConversionFactor();
    c.getShader();
    c.setFactorUniform();
  }
}
