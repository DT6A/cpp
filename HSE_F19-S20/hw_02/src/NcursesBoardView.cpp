#include <ncurses.h>
#include <iostream>
#include <string>

#include "NcursesBoardView.h"

NcursesBoardView::NcursesBoardView(Board &board) : _board{board}, cur_x{0}, cur_y{0}
{

}

void NcursesBoardView::startGame()
{
  initscr();
  start_color();

  init_pair(X_PAIR, COLOR_RED, COLOR_BLACK);
  init_pair(O_PAIR, COLOR_GREEN, COLOR_BLACK);
  init_pair(E_PAIR, COLOR_WHITE, COLOR_BLACK);

  printBoard();
  refresh();

  noecho();
}

void NcursesBoardView::printBoard() const
{
  for (int i = 0; i < Board::BOARD_SIZE; ++i)
    for (int j = 0; j < Board::BOARD_SIZE; ++j)
    {
      BoardSign sign = _board(Point(j, i));

      if (sign == BoardSign::O)
      {
        attron(COLOR_PAIR(O_PAIR));
        mvaddch(i, j, 'O');
        attroff(COLOR_PAIR(O_PAIR));
      }
      else if (sign == BoardSign::X)
      {
        attron(COLOR_PAIR(X_PAIR));
        mvaddch(i, j, 'X');
        attroff(COLOR_PAIR(X_PAIR));
      }
      else
      {
        attron(COLOR_PAIR(E_PAIR));
        mvaddch(i, j, '.');
        attroff(COLOR_PAIR(E_PAIR));
      }

    }
  refresh();
}

void NcursesBoardView::endMove() const
{
  printBoard();
}

std::optional<Point> NcursesBoardView::getInput()
{
  Point coord(-2, -2);
  std::optional<BoardPlayer> player = _board.getPlayer();

  if (!player)
  {
    coord = EXIT_MARK;
    return {};
  }

  if (player == BoardPlayer::XPlayer)
  {
    attron(COLOR_PAIR(X_PAIR));
    mvaddstr(Board::BOARD_SIZE, 0, "X turn");
    attroff(COLOR_PAIR(X_PAIR));
  }
  else
  {
    attron(COLOR_PAIR(O_PAIR));
    mvaddstr(Board::BOARD_SIZE, 0, "O turn");
    attroff(COLOR_PAIR(O_PAIR));
  }
  while (true)
  {
    move(cur_y, cur_x);
    int ch = getch();
    if (ch == 32)
    {
      coord.x = cur_x, coord.y = cur_y;
      break;
    }
    else if (ch == 120)
    {
      coord.x = -1, coord.y = -1;
      break;
    }
    else if (ch == 67)
      cur_x = std::min(cur_x + 1, 9);
    else if (ch == 66)
      cur_y = std::min(cur_y + 1, 9);
    else if (ch == 68)
      cur_x = std::max(cur_x - 1, 0);
    else if (ch == 65)
      cur_y = std::max(cur_y - 1, 0);
  }
  return coord;
}

void NcursesBoardView::badMove() const
{

}

void NcursesBoardView::endGame() const
{
  printBoard();

  std::string GameResult;

  if (_board.getState() == BoardStates::win_O)
  {
    attron(COLOR_PAIR(O_PAIR));
    GameResult = "O wins!";
  }
  else if (_board.getState() == BoardStates::win_X)
  {
    attron(COLOR_PAIR(X_PAIR));
    GameResult = "X wins!";
  }
  else if (_board.getState() == BoardStates::draw)
  {
    attron(COLOR_PAIR(E_PAIR));
    GameResult = "Draw.";
  }
  mvaddstr(Board::BOARD_SIZE, 0, GameResult.c_str());
  refresh();
  if (_board.getState() != BoardStates::continues)
    getch();

  endwin();
}
