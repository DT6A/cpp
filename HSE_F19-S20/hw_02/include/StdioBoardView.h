#ifndef __STDIO_BOARD_VIEW_H
#define __STDIO_BOARD_VIEW_H

#include "BoardView.h"
#include "Board.h"

enum Players
{
  player_X, player_O
};

class StdioBoardView final : public BoardView
{
public:
  enum Modes
  {
    DEFAULT, SILENT
  };

private:
  Board &_board;
  Modes _mode;

public:
  explicit StdioBoardView(Board &board, Modes mode = DEFAULT);

  void printBoard() const override;
  void endMove() const override;
  void startGame() override;
  std::optional<Point> getInput() override;
  void badMove() const override;
  void endGame() const override;
};

#endif //__STDIO_BOARD_VIEW_H
