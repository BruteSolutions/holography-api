#ifndef TEST_MONITOR_H_
#define TEST_MONITOR_H_

#include "TestCase.h"

class TestMonitor : public TestCase
{
  public:
    TestMonitor();
    void run();
    std::string componentName() { return("Monitor"); }
};

#endif
