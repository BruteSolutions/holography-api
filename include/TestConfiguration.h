#ifndef TEST_CONFIGURATION_H_
#define TEST_CONFIGURATION_H_

#include <fstream>
#include "TestCase.h"

class TestConfiguration : public TestCase
{
  public:
    TestConfiguration();
    void run();
  private:
    std::ofstream of;
};

#endif
