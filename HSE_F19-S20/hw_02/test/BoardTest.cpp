#include "Board.h"
#include "BoardTest.h"

void BoardTest::testStart()
{
  Board b;

  DO_CHECK(b.getState() == BoardStates::continues);
}

void BoardTest::testFirstRightMove()
{
  for (int i = 0; i < Board::BOARD_SIZE; ++i)
    for (int j = 0; j < Board::BOARD_SIZE; ++j)
      DO_CHECK(Board().canMove(Point(j, i), BoardPlayer::OPlayer) == true);

  for (int i = 0; i < Board::BOARD_SIZE; ++i)
    for (int j = 0; j < Board::BOARD_SIZE; ++j)
      DO_CHECK(Board().canMove(Point(j, i), BoardPlayer::XPlayer) == false);
}

void BoardTest::testFirstWrongMove()
{
  for (int i = -5; i < 0; ++i)
    for (int j = -5; j < Board::BOARD_SIZE + 5; ++j)
    {
      DO_CHECK(Board().canMove(Point(j, i), BoardPlayer::OPlayer) == false);
      DO_CHECK(Board().canMove(Point(i, j), BoardPlayer::OPlayer) == false);
    }
  for (int i = Board::BOARD_SIZE; i < Board::BOARD_SIZE + 5; ++i)
    for (int j = -5; j < Board::BOARD_SIZE + 5; ++j)
    {
      DO_CHECK(Board().canMove(Point(j, i), BoardPlayer::OPlayer) == false);
      DO_CHECK(Board().canMove(Point(i, j), BoardPlayer::OPlayer) == false);
    }
}

void BoardTest::testMove()
{
  for (int i = 0; i < Board::BOARD_SIZE; ++i)
    for (int j = 0; j < Board::BOARD_SIZE; ++j)
    {
      Board b;
      DO_CHECK(b.canMove(Point(j, i), BoardPlayer::OPlayer));
      b.move(Point(j, i), BoardPlayer::OPlayer);
      DO_CHECK(b.canMove(Point(j, i), BoardPlayer::OPlayer) == false);
      DO_CHECK(b.canMove(Point(j, i), BoardPlayer::XPlayer) == false);
    }
}

void BoardTest::testOWins()
{
  for (int i = 0; i < Board::BOARD_SIZE - 5; ++i)
    for (int j = 0; j < Board::BOARD_SIZE; ++j)
    {
      {
        Board b;
        for (int k = 0; k < 5; ++k)
        {
          b.setPlayer(BoardPlayer::OPlayer);
          DO_CHECK(b.canMove(Point(j, i + k), BoardPlayer::OPlayer));
          b.move(Point(j, i + k), BoardPlayer::OPlayer);
        }
        DO_CHECK(b.getState() == BoardStates::win_O);
      }
      {
        Board b;
        for (int k = 0; k < 5; ++k)
        {
          b.setPlayer(BoardPlayer::OPlayer);
          DO_CHECK(b.canMove(Point(i + k, j), BoardPlayer::OPlayer));
          b.move(Point(i + k, j), BoardPlayer::OPlayer);
        }
        DO_CHECK(b.getState() == BoardStates::win_O);
      }
    }
  for (int i = 0; i < Board::BOARD_SIZE - 5; ++i)
    for (int j = 0; j < Board::BOARD_SIZE - 5; ++j)
    {
      {
        Board b;
        for (int k = 0; k < 5; ++k)
        {
          b.setPlayer(BoardPlayer::OPlayer);
          DO_CHECK(b.canMove(Point(j + k, i + k), BoardPlayer::OPlayer));
          b.move(Point(j + k, i + k), BoardPlayer::OPlayer);
        }
        DO_CHECK(b.getState() == BoardStates::win_O);
      }
      {
        Board b;
        for (int k = 0; k < 5; ++k)
        {
          b.setPlayer(BoardPlayer::OPlayer);
          DO_CHECK(b.canMove(Point(j + 4 - k, i + k), BoardPlayer::OPlayer));
          b.move(Point(j + 4 - k, i + k), BoardPlayer::OPlayer);
        }
        DO_CHECK(b.getState() == BoardStates::win_O);
      }
    }
}

void BoardTest::testXWins()
{
  for (int i = 0; i < Board::BOARD_SIZE - 5; ++i)
    for (int j = 0; j < Board::BOARD_SIZE; ++j)
    {
      {
        Board b;
        for (int k = 0; k < 5; ++k)
        {
          b.setPlayer(BoardPlayer::XPlayer);
          DO_CHECK(b.canMove(Point(j, i + k), BoardPlayer::XPlayer));
          b.move(Point(j, i + k), BoardPlayer::XPlayer);
        }
        DO_CHECK(b.getState() == BoardStates::win_X);
      }
      {
        Board b;
        for (int k = 0; k < 5; ++k)
        {
          b.setPlayer(BoardPlayer::XPlayer);
          DO_CHECK(b.canMove(Point(i + k, j), BoardPlayer::XPlayer));
          b.move(Point(i + k, j), BoardPlayer::XPlayer);
        }
        DO_CHECK(b.getState() == BoardStates::win_X);
      }
    }
  for (int i = 0; i < Board::BOARD_SIZE - 5; ++i)
    for (int j = 0; j < Board::BOARD_SIZE - 5; ++j)
    {
      {
        Board b;
        for (int k = 0; k < 5; ++k)
        {
          b.setPlayer(BoardPlayer::XPlayer);
          DO_CHECK(b.canMove(Point(j + k, i + k), BoardPlayer::XPlayer));
          b.move(Point(j + k, i + k), BoardPlayer::XPlayer);
        }
        DO_CHECK(b.getState() == BoardStates::win_X);
      }
      {
        Board b;
        for (int k = 0; k < 5; ++k)
        {
          b.setPlayer(BoardPlayer::XPlayer);
          DO_CHECK(b.canMove(Point(j + 4 - k, i + k), BoardPlayer::XPlayer));
          b.move(Point(j + 4 - k, i + k), BoardPlayer::XPlayer);
        }
        DO_CHECK(b.getState() == BoardStates::win_X);
      }
    }
}

void BoardTest::testDraw10()
{
  Board b;

  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(0, 0), BoardPlayer::OPlayer));
  b.move(Point(0, 0), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(1, 0), BoardPlayer::OPlayer));
  b.move(Point(1, 0), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(2, 0), BoardPlayer::OPlayer));
  b.move(Point(2, 0), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(3, 0), BoardPlayer::XPlayer));
  b.move(Point(3, 0), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(4, 0), BoardPlayer::OPlayer));
  b.move(Point(4, 0), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(5, 0), BoardPlayer::OPlayer));
  b.move(Point(5, 0), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(6, 0), BoardPlayer::OPlayer));
  b.move(Point(6, 0), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(7, 0), BoardPlayer::XPlayer));
  b.move(Point(7, 0), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(8, 0), BoardPlayer::OPlayer));
  b.move(Point(8, 0), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(9, 0), BoardPlayer::OPlayer));
  b.move(Point(9, 0), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.getState() == BoardStates::continues);

  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(0, 1), BoardPlayer::OPlayer));
  b.move(Point(0, 1), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(1, 1), BoardPlayer::OPlayer));
  b.move(Point(1, 1), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(2, 1), BoardPlayer::OPlayer));
  b.move(Point(2, 1), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(3, 1), BoardPlayer::XPlayer));
  b.move(Point(3, 1), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(4, 1), BoardPlayer::OPlayer));
  b.move(Point(4, 1), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(5, 1), BoardPlayer::OPlayer));
  b.move(Point(5, 1), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(6, 1), BoardPlayer::OPlayer));
  b.move(Point(6, 1), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(7, 1), BoardPlayer::XPlayer));
  b.move(Point(7, 1), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(8, 1), BoardPlayer::OPlayer));
  b.move(Point(8, 1), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(9, 1), BoardPlayer::OPlayer));
  b.move(Point(9, 1), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.getState() == BoardStates::continues);

  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(0, 2), BoardPlayer::OPlayer));
  b.move(Point(0, 2), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(1, 2), BoardPlayer::OPlayer));
  b.move(Point(1, 2), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(2, 2), BoardPlayer::OPlayer));
  b.move(Point(2, 2), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(3, 2), BoardPlayer::XPlayer));
  b.move(Point(3, 2), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(4, 2), BoardPlayer::OPlayer));
  b.move(Point(4, 2), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(5, 2), BoardPlayer::OPlayer));
  b.move(Point(5, 2), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(6, 2), BoardPlayer::OPlayer));
  b.move(Point(6, 2), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(7, 2), BoardPlayer::XPlayer));
  b.move(Point(7, 2), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(8, 2), BoardPlayer::OPlayer));
  b.move(Point(8, 2), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(9, 2), BoardPlayer::OPlayer));
  b.move(Point(9, 2), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.getState() == BoardStates::continues);

  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(0, 3), BoardPlayer::XPlayer));
  b.move(Point(0, 3), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(1, 3), BoardPlayer::OPlayer));
  b.move(Point(1, 3), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(2, 3), BoardPlayer::OPlayer));
  b.move(Point(2, 3), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(3, 3), BoardPlayer::XPlayer));
  b.move(Point(3, 3), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(4, 3), BoardPlayer::OPlayer));
  b.move(Point(4, 3), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(5, 3), BoardPlayer::XPlayer));
  b.move(Point(5, 3), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(6, 3), BoardPlayer::XPlayer));
  b.move(Point(6, 3), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(7, 3), BoardPlayer::XPlayer));
  b.move(Point(7, 3), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(8, 3), BoardPlayer::OPlayer));
  b.move(Point(8, 3), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(9, 3), BoardPlayer::OPlayer));
  b.move(Point(9, 3), BoardPlayer::OPlayer);
  DO_CHECK(b.getState() == BoardStates::continues);

  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(0, 4), BoardPlayer::OPlayer));
  b.move(Point(0, 4), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(1, 4), BoardPlayer::OPlayer));
  b.move(Point(1, 4), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(2, 4), BoardPlayer::OPlayer));
  b.move(Point(2, 4), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(3, 4), BoardPlayer::OPlayer));
  b.move(Point(3, 4), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(4, 4), BoardPlayer::XPlayer));
  b.move(Point(4, 4), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(5, 4), BoardPlayer::OPlayer));
  b.move(Point(5, 4), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(6, 4), BoardPlayer::OPlayer));
  b.move(Point(6, 4), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(7, 4), BoardPlayer::OPlayer));
  b.move(Point(7, 4), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(8, 4), BoardPlayer::XPlayer));
  b.move(Point(8, 4), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(9, 4), BoardPlayer::XPlayer));
  b.move(Point(9, 4), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.getState() == BoardStates::continues);

  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(0, 5), BoardPlayer::XPlayer));
  b.move(Point(0, 5), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(1, 5), BoardPlayer::XPlayer));
  b.move(Point(1, 5), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(2, 5), BoardPlayer::XPlayer));
  b.move(Point(2, 5), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(3, 5), BoardPlayer::XPlayer));
  b.move(Point(3, 5), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(4, 5), BoardPlayer::OPlayer));
  b.move(Point(4, 5), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(5, 5), BoardPlayer::XPlayer));
  b.move(Point(5, 5), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(6, 5), BoardPlayer::XPlayer));
  b.move(Point(6, 5), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(7, 5), BoardPlayer::XPlayer));
  b.move(Point(7, 5), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(8, 5), BoardPlayer::OPlayer));
  b.move(Point(8, 5), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(9, 5), BoardPlayer::OPlayer));
  b.move(Point(9, 5), BoardPlayer::OPlayer);
  DO_CHECK(b.getState() == BoardStates::continues);

  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(0, 6), BoardPlayer::OPlayer));
  b.move(Point(0, 6), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(1, 6), BoardPlayer::OPlayer));
  b.move(Point(1, 6), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(2, 6), BoardPlayer::OPlayer));
  b.move(Point(2, 6), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(3, 6), BoardPlayer::XPlayer));
  b.move(Point(3, 6), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(4, 6), BoardPlayer::OPlayer));
  b.move(Point(4, 6), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(5, 6), BoardPlayer::XPlayer));
  b.move(Point(5, 6), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(6, 6), BoardPlayer::XPlayer));
  b.move(Point(6, 6), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(7, 6), BoardPlayer::XPlayer));
  b.move(Point(7, 6), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(8, 6), BoardPlayer::XPlayer));
  b.move(Point(8, 6), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(9, 6), BoardPlayer::OPlayer));
  b.move(Point(9, 6), BoardPlayer::OPlayer);
  DO_CHECK(b.getState() == BoardStates::continues);

  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(0, 7), BoardPlayer::XPlayer));
  b.move(Point(0, 7), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(1, 7), BoardPlayer::XPlayer));
  b.move(Point(1, 7), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(2, 7), BoardPlayer::XPlayer));
  b.move(Point(2, 7), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(3, 7), BoardPlayer::XPlayer));
  b.move(Point(3, 7), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(4, 7), BoardPlayer::OPlayer));
  b.move(Point(4, 7), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(5, 7), BoardPlayer::OPlayer));
  b.move(Point(5, 7), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(6, 7), BoardPlayer::OPlayer));
  b.move(Point(6, 7), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(7, 7), BoardPlayer::OPlayer));
  b.move(Point(7, 7), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(8, 7), BoardPlayer::XPlayer));
  b.move(Point(8, 7), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(9, 7), BoardPlayer::XPlayer));
  b.move(Point(9, 7), BoardPlayer::XPlayer);
  DO_CHECK(b.getState() == BoardStates::continues);

  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(0, 8), BoardPlayer::OPlayer));
  b.move(Point(0, 8), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(1, 8), BoardPlayer::OPlayer));
  b.move(Point(1, 8), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(2, 8), BoardPlayer::OPlayer));
  b.move(Point(2, 8), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(3, 8), BoardPlayer::OPlayer));
  b.move(Point(3, 8), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(4, 8), BoardPlayer::XPlayer));
  b.move(Point(4, 8), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(5, 8), BoardPlayer::OPlayer));
  b.move(Point(5, 8), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(6, 8), BoardPlayer::OPlayer));
  b.move(Point(6, 8), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(7, 8), BoardPlayer::OPlayer));
  b.move(Point(7, 8), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(8, 8), BoardPlayer::OPlayer));
  b.move(Point(8, 8), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(9, 8), BoardPlayer::XPlayer));
  b.move(Point(9, 8), BoardPlayer::XPlayer);
  DO_CHECK(b.getState() == BoardStates::continues);

  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(0, 9), BoardPlayer::XPlayer));
  b.move(Point(0, 9), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(1, 9), BoardPlayer::XPlayer));
  b.move(Point(1, 9), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(2, 9), BoardPlayer::XPlayer));
  b.move(Point(2, 9), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(3, 9), BoardPlayer::XPlayer));
  b.move(Point(3, 9), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(4, 9), BoardPlayer::OPlayer));
  b.move(Point(4, 9), BoardPlayer::OPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(5, 9), BoardPlayer::XPlayer));
  b.move(Point(5, 9), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(6, 9), BoardPlayer::XPlayer));
  b.move(Point(6, 9), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(7, 9), BoardPlayer::XPlayer));
  b.move(Point(7, 9), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(8, 9), BoardPlayer::XPlayer));
  b.move(Point(8, 9), BoardPlayer::XPlayer);
  b.setPlayer(BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(9, 9), BoardPlayer::OPlayer));
  b.move(Point(9, 9), BoardPlayer::OPlayer);
  DO_CHECK(b.getState() == BoardStates::draw);
}

void BoardTest::testCanMove()
{
  Board b;

  DO_CHECK(b.canMove(Point(0, 0), BoardPlayer::XPlayer) == false);
  b.move(Point(0, 0), BoardPlayer::OPlayer);
  DO_CHECK(b.canMove(Point(0, 1), BoardPlayer::OPlayer) == false);
  b.move(Point(0, 1), BoardPlayer::XPlayer);
  DO_CHECK(b.canMove(Point(0, 1), BoardPlayer::XPlayer) == false);

}

void BoardTest::runAllTests()
{
  testStart();
  testFirstRightMove();
  testFirstWrongMove();
  testMove();
  testOWins();
  testXWins();
  testDraw10();
  testCanMove();
}