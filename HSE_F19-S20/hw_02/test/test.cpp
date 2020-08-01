#include "BoardTest.h"

int main()
{
  BoardTest bt;

  bt.runAllTests();
  bt.showFinalResult();

  return bt.failedNum != 0;
}