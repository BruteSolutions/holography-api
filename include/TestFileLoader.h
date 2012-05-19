#ifndef TEST_FILELOADER_H_
#define TEST_FILELOADER_H_

#include "TestCase.h"

class TestFileLoader : public TestCase
{
  public:
    TestFileLoader();
    void run();
    std::string componentName() { return("FileLoader"); }
};

#endif
