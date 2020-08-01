#include "GameController.h"

GameController::GameController(Board &board, BoardView &view) : _board{board}, _view{view}
{

}

void GameController::doGameCycle()
{
  _view.startGame();

  while (_board.getState() == BoardStates::continues)
  {
    std::optional<Point> inputCoord({-2, -2});
    Point moveCoord(-2, -2);
    while (true)
    {
      inputCoord = _view.getInput();

      if (!inputCoord)
        return;

      moveCoord = *inputCoord;

      if (_board.canMove(moveCoord, _board.getPlayer()) || moveCoord == BoardView::EXIT_MARK)
        break;
      _view.badMove();
    }

    if (moveCoord == BoardView::EXIT_MARK)
      break;
    _board.move(moveCoord, _board.getPlayer());
    if (_board.getState() == BoardStates::continues)
      _view.endMove();
  }

  _view.endGame();
}
