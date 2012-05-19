#ifndef TESTFRAMEWORK_H_
#define TESTFRAMEWORK_H_

#include "TestCase.h"
#include <vector>

class TestFramework
{
  public:
    TestFramework();
    void addTestCase(TestCase * testCase);
    bool test();

  private:
    std::vector<TestCase*> tests;
};

#endif
