#include <cstdio>
#include <cassert>
#include <cstring>

#include "Circle.hpp"

Circle::Circle(int id, int x, int y, int r, const char* label) : Figure{id, x, y},
  radius{r}
{
  assert(label != nullptr);

  this->label = new char[strlen(label) + 1];
  strcpy(this->label, label);
}

Circle::~Circle()
{
  delete[] label;
}

void Circle::print() const
{
  printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id, x, y, radius, label);
}

bool Circle::is_inside(int point_x, int point_y) const
{
  return (1LL * point_x - x) * (point_x - x) + (1LL * point_y - y) * 
    (point_y - y) <= 1LL * radius * radius;
}

void Circle::zoom(int factor)
{
  radius *= factor;
}