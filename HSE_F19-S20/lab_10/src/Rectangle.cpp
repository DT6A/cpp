#include <cstdio>

#include "Rectangle.hpp"

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure{id, x, y},
  width{width}, height{height}
{

}

Rectangle::~Rectangle()
{
  
}

void Rectangle::print() const
{
  printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id, x, y, width, height);
}

bool Rectangle::is_inside(int point_x, int point_y) const
{
  return (2 * point_x <= 2 * x + width) && (2 * point_x >= 2 * x - width) &&
    (2 * point_y <= 2 * y + height) && (2 * point_y >= 2 * y - height);
}

void Rectangle::zoom(int factor)
{
  width *= factor;
  height *= factor;
}