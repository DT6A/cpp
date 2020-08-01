#ifndef __BOARD_H
#define __BOARD_H

#include <optional>

enum class BoardSign
{
  Empty, X, O
};

enum class BoardPlayer
{
  XPlayer, OPlayer
};

enum class BoardStates
{
  draw, win_X, win_O, continues
};

struct Point
{
  int x, y;

  Point(const int x_coord, const int y_coord);
  bool operator==(const Point &other) const;
};

class Board final
{
public:
  static constexpr const int BOARD_SIZE = 10;

private:
  BoardSign _data[BOARD_SIZE][BOARD_SIZE];
  BoardStates _state;
  BoardPlayer _player;

  void update_state();
  bool checkDirection(const Point &coord, const Point &dir);
  bool checkFull();

public:
  /** Проверить ход на корректность, если бы он был следующим. */
  bool canMove(const Point &coord, std::optional<BoardPlayer> player) const;
  /** Сделать ход. UB если он некорректен. */
  void move(const Point &coord, std::optional<BoardPlayer> player);
  /** Состояние игры: игра идёт, игра кончилась с одним из результатов: ничья, победа одной из сторон. */
  BoardStates getState() const;
  std::optional<BoardPlayer> getPlayer() const;
  BoardSign getCell(const Point &coord) const ;
  BoardSign operator()(const Point &coord) const;

  void setPlayer(BoardPlayer player);

  Board();
};

#endif //__BOARD_H
