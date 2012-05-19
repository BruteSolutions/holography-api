#ifndef TEST_PROJECTOR_H_
#define TEST_PROJECTOR_H_

#include "TestCase.h"

class TestProjector : public TestCase
{
  public:
    TestProjector();
    void run();
    std::string componentName() { return("Projector"); }
};

#endif
