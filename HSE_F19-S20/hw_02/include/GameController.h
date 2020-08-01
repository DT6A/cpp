#ifndef __GAME_CONTROLLER_H
#define __GAME_CONTROLLER_H

#include "BoardView.h"

class GameController
{
private:
  Board &_board;
  BoardView &_view;

public:
  GameController(Board &board, BoardView &View);
  void doGameCycle();
};

#endif //__GAME_CONTROLLER_H
