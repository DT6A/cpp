#include <iostream>

#include "Test.h"

int Test::totalNum = 0, Test::failedNum = 0;

void Test::check(bool expr, const char *func, const char *filename, std::size_t lineNum)
{
  totalNum++;
  if (!expr)
  {
    std::cout << "Failed test. In \'" << filename
      << "\' function \'" << func << "\' line " << lineNum << '\n';
    failedNum++;
  }
}

void Test::showFinalResult()
{
  std::cout << "Failed " << failedNum << " of " << totalNum << " tests\n";
}
