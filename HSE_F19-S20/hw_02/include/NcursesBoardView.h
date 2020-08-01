#ifndef __NCURSES_BOARD_VIEW_H
#define __NCURSES_BOARD_VIEW_H

#include "BoardView.h"

class NcursesBoardView final : public BoardView
{
private:
  Board &_board;
  int cur_x, cur_y;

  static constexpr const int X_PAIR = 1;
  static constexpr const int O_PAIR = 2;
  static constexpr const int E_PAIR = 3;

public:
  explicit NcursesBoardView(Board &board);

  void startGame() override;
  void printBoard() const override;
  void endMove() const override;
  std::optional<Point> getInput() override;
  void badMove() const override;
  void endGame() const override;
};

#endif //__NCURSES_BOARD_VIEW_H
