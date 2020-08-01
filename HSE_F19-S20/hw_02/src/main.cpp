#include <string>

#include "Board.h"
#include "StdioBoardView.h"
#include "NcursesBoardView.h"
#include "GameController.h"

int main(int argc, char *argv[])
{
  Board board;
  BoardView *View = nullptr;

  if (argc > 1)
  {
    if (argv[1] == std::string("silent"))
      View = new StdioBoardView(board, StdioBoardView::Modes::SILENT);
    else if (argv[1] == std::string("curses"))
      View = new NcursesBoardView(board);
    else
      View = new StdioBoardView(board);
  }
  else
    View = new StdioBoardView(board);

  GameController contrl(board, *View);
  contrl.doGameCycle();

  delete View;
  return 0;
}
