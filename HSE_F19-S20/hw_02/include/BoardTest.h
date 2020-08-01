#ifndef __BOARD_TEST_H
#define __BOARD_TEST_H

#include "Test.h"

class BoardTest final : public Test
{
private:
  void testStart();
  void testFirstRightMove();
  void testFirstWrongMove();
  void testMove();
  void testOWins();
  void testXWins();
  void testDraw10();
  void testCanMove();

public:
  void runAllTests() override;
};

#endif //__BOARD_TEST_H
