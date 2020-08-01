#include <iostream>

#include "HuffmanExceptions.h"
#include "CLI.h"

int main(int argc, const char *argv[])
{
  try
  {
    CLI cli(argc, argv);
    cli.run();
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << '\n';
    return 1;
  }
  return 0;
}
