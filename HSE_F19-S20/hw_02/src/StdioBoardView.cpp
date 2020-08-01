#include <cstdio>

#include "StdioBoardView.h"

StdioBoardView::StdioBoardView(Board &board, Modes mode) : _board{board}, _mode{mode}
{

}

void StdioBoardView::printBoard() const
{
  printf("\n");
  for (int i = 0; i < Board::BOARD_SIZE; ++i)
  {
    for (int j = 0; j < Board::BOARD_SIZE; ++j)
      switch (_board(Point(i, j)))
      {
        case BoardSign::X:
          printf("X");
          break;
        case BoardSign::O:
          printf("O");
          break;
        default:
          printf(".");
      }
    printf("\n");
  }
}

void StdioBoardView::endMove() const
{
  if (_mode != SILENT)
    printBoard();
}

void StdioBoardView::startGame()
{
  endMove();
}

std::optional<Point> StdioBoardView::getInput()
{
  Point coord(-2, -2);
  bool goodInput = false;
  std::optional<BoardPlayer> player = _board.getPlayer();

  if (!player)
  {
    printf("Can't make move\n");
    return {};
  }

  char line[1000];

  while (!goodInput)
  {
    goodInput = true;
    if (player == BoardPlayer::OPlayer)
      printf("O move:");
    else
      printf("X move:");
    fgets(line, 1000, stdin);

    char space;
    if (sscanf(line, "%d%c %d", &coord.x, &space, &coord.y) != 3 || space != ' ')
    {
      badMove();
      goodInput = false;
    }
  }
  return coord;
}

void StdioBoardView::badMove() const
{
  printf("Bad move!\n");
}

void StdioBoardView::endGame() const
{
  if (_board.getState() != BoardStates::continues)
    printBoard();

  switch (_board.getState())
  {
    case BoardStates::win_X:
      printf("X wins!\n");
      break;
    case BoardStates::win_O:
      printf("O wins!\n");
      break;
    case BoardStates::draw:
      printf("Draw.\n");
      break;
    default:
      break;
  }
}