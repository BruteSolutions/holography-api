#include "TestFramework.h"
#include <iostream>

TestFramework::TestFramework()
{
}


void TestFramework::addTestCase(TestCase * testCase)
{
  tests.push_back(testCase);
}

bool TestFramework::test()
{
  std::vector<TestCase*>::iterator it;
  for(it = tests.begin(); it != tests.end(); it++) 
  {
    try
    {
      std::cout << "[*] Testing component: " << (*it)->componentName()
                << ".. ";
      (*it)->run();
    }
    catch(...)
    {
      std::cout << "failure." << std::endl;
      return(false);
    }

    std::cout << "success." << std::endl;
  }

  return(true);
}
