#ifndef __BOARD_VIEW_H
#define __BOARD_VIEW_H

#include <optional>

#include "Board.h"

class BoardView
{
public:
  static const Point EXIT_MARK;

  virtual ~BoardView() = default;

  virtual void startGame() = 0;
  virtual void printBoard() const = 0;
  virtual void endMove() const = 0;
  virtual std::optional<Point> getInput() = 0;
  virtual void badMove() const = 0;
  virtual void endGame() const = 0;
};

#endif //__BOARD_VIEW_H
