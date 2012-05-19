#ifndef TESTCASE_H_
#define TESTCASE_H_

#include <iostream>

class TestCase
{
  public:
    TestCase() {};
    virtual void run() = 0;
    virtual std::string componentName() = 0;
};

#endif
