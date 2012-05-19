#ifndef TEST_DISPLAY_H_
#define TEST_DISPLAY_H_

#include "TestCase.h"

class TestDisplay : public TestCase
{
  public:
    TestDisplay();
    void run();
    std::string componentName() { return("Display"); }
};

#endif
