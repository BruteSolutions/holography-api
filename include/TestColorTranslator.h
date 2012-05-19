#ifndef TEST_COLORTRANSLATOR_H_
#define TEST_COLORTRANSLATOR_H_

#include "TestCase.h"

class TestColorTranslator : public TestCase
{
  public:
    TestColorTranslator();
    void run();
    std::string componentName() { return("ColorTranslator"); }
};

#endif
