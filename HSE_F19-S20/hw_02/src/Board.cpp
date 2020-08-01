#include <iostream>
#include <cassert>

#include "Board.h"

Point::Point(const int x_coord, const int y_coord) : x{x_coord}, y{y_coord}
{

}

bool Point::operator==(const Point &other) const
{
  return x == other.x && y == other.y;
}

Board::Board() : _state{BoardStates::continues}, _player{BoardPlayer::OPlayer}
{
  for (int i = 0; i < BOARD_SIZE; ++i)
    for (int j = 0; j < BOARD_SIZE; ++j)
      _data[i][j] = BoardSign::Empty;
}

bool Board::checkFull()
{
  for (int i = 0; i < BOARD_SIZE; ++i)
    for (int j = 0; j < BOARD_SIZE; ++j)
      if (_data[i][j] == BoardSign::Empty)
        return false;

  _state = BoardStates::draw;
  return true;
}

bool Board::checkDirection(const Point &coord, const Point &dir)
{
  int x = coord.x, y = coord.y, dx = dir.x, dy = dir.y;

  if (_data[y][x] == BoardSign::Empty)
    return false;

  for (int i = 1; i <= 4; ++i)
    if (y + i * dy >= BOARD_SIZE || x + i * dx >= BOARD_SIZE ||
          y + i * dy < 0 || x + i * dx < 0 ||
          _data[y][x] != _data[y + i * dy][x + i * dx])
      return false;

  if (_data[y][x] == BoardSign::X)
    _state = BoardStates::win_X;
  else
    _state = BoardStates::win_O;

  return true;
}

void Board::update_state()
{
  if (_state != BoardStates::continues)
    return;

  for (int i = 0; i < BOARD_SIZE; ++i)
    for (int j = 0; j < BOARD_SIZE; ++j)
    {
      checkDirection(Point(j, i), Point(0, 1));
      for (int dy = -1; dy <= 1; ++dy)
        checkDirection(Point(j, i), Point(1, dy));
    }
  if (_state == BoardStates::continues)
    checkFull();
}

BoardStates Board::getState() const
{
  return _state;
}
std::optional<BoardPlayer> Board::getPlayer() const
{
  if (_state == BoardStates::continues)
    return std::optional<BoardPlayer>(_player);
  return {};
}

BoardSign Board::getCell(const Point &coord) const
{
  int x = coord.x, y = coord.y;

  assert(x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE);
  return _data[y][x];
}

BoardSign Board::operator()(const Point &coord) const
{
  return getCell(coord);
}

bool Board::canMove(const Point &coord, std::optional<BoardPlayer> player) const
{
  int x = coord.x, y = coord.y;
  if (!player || x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || player != _player)
    return false;
  return _data[y][x] == BoardSign::Empty;
}

void Board::move(const Point &coord, std::optional<BoardPlayer> player)
{
  int x = coord.x, y = coord.y;

  if (player == BoardPlayer::OPlayer)
    _data[y][x] = BoardSign::O;
  else if (player == BoardPlayer::XPlayer)
    _data[y][x] = BoardSign::X;

  update_state();

  if (player == BoardPlayer::OPlayer)
    _player = BoardPlayer::XPlayer;
  else if (player == BoardPlayer::XPlayer)
    _player = BoardPlayer::OPlayer;
}

void Board::setPlayer(BoardPlayer player)
{
  _player = player;
}
