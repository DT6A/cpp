#include <iostream>
#include <string>

#include "employees.h"

int main()
{
  std::string cmd;
  EmployeesArray arr;

  while (true)
  {
    std::cin >> cmd >> stream_checker();

    if (cmd == "exit")
      break;
    else if (cmd == "add")
      std::cin >> arr >> stream_checker();
    else if (cmd == "list")
      std::cout << arr << stream_checker();
    else if (cmd == "save")
    {
      std::string path;
      std::cin >> path >> stream_checker();
      std::ofstream of(path);
      of << arr << stream_checker();
    }
    else if (cmd == "load")
    {
      std::string path;
      std::cin >> path >> stream_checker();
      std::ifstream inf(path);
      inf >> arr >> stream_checker();
    }
  }

  return 0;
}
