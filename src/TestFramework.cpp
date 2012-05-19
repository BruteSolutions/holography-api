#include "TestFramework.h"

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
      (*it)->run();
    }
    catch(...)
    {
      return(false);
    }
  }

  return(true);
}
