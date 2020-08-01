#include "Figure.hpp"

class Rectangle : public Figure {
public:
  Rectangle(int id, int x, int y, int width, int height);
  ~Rectangle();

  void print() const override;
  bool is_inside(int point_x, int point_y) const override;
  void zoom(int factor) override;

private:
  int width, height;
};
