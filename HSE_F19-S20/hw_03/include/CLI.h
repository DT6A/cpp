#ifndef CLI_H
#define CLI_H

#include <string>

class CLI final
{
public:
  enum ArchiverMode
  {
    UNDEFINED,
    COMPRESS,
    EXTRACT
  };

  explicit CLI(int argc, const char *argv[]);

  void run();

  std::string getInputFileName() noexcept;

  std::string getOutputFileName() noexcept;

  ArchiverMode getMode() const noexcept;
private:
  ArchiverMode mode_ = UNDEFINED;

  std::string inFileName_, outFileName_;
};

#endif //CLI_H
