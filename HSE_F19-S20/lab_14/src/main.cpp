#include <iostream>
#include <string>
#include <stdexcept>

#include "matrix.h"

int getId()
{
  std::string reg;

  std::cin >> reg;

  if (reg.length() != 2 || reg[0] != '$')
    throw std::logic_error("Wrong index");

  int number = reg[1] - '0';

  if (number > 9 || number < 0)
    throw std::logic_error("Wrong index");

  return number;
}

int main()
{
  Matrix matricies[10];
  std::string command;

  while (std::cin >> command)
  {
    try
    {
      if (command == "load")
      {
        std::string fn;
        int number = getId();

        std::cin >> fn;

        matricies[number] = Matrix(fn);
      }
      else if (command == "print")
      {
        int number = getId();

        matricies[number].print();
      }
      else if (command == "add")
      {
        int n1 = getId(), n2 = getId();

        matricies[n1] += matricies[n2];
      }
      else if (command == "mul")
      {
        int n1 = getId(), n2 = getId();

        matricies[n1] *= matricies[n2];
      }
      else if (command == "elem")
      {
        int number = getId(), row, col;

        std::cin >> row >> col;

        std::cout << matricies[number].getElement(row, col) << '\n';
      }
      else if (command == "exit")
        return 0;
    }
    catch (const std::bad_alloc &e)
    {
      std::cout << "Unable to allocate memory.\n";
    }
    catch (const std::exception &e)
    {
      std::cout << e.what() << '\n';
    }
    catch (...)
    {
      std::cout << "Unknown error\n";
    }
  }

  return 0;
}
