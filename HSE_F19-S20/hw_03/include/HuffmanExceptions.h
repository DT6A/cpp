#ifndef HUFFMAN_EXCEPTIONS_H
#define HUFFMAN_EXCEPTIONS_H

#include <exception>

namespace huffman
{
class HuffmanArchiverException final : public std::exception
{
public:
  enum ExceptType
  {
    INVALID_FILE_FORMAT,
    CORRUPTED_FILE,
    NONE
  };

  explicit HuffmanArchiverException(const ExceptType type) noexcept;

  const char* what() const noexcept override;

  ExceptType getType() const noexcept;

private:
  ExceptType type_ = NONE;
};

class HuffmanCLIException final : public std::exception
{
public:
  enum ExceptType
  {
    INVALID_FLAGS = 1,
    UNDEFINED_INPUT_FILE,
    UNDEFINED_OUTPUT_FILE,
    UNDEFINED_CLI_MODE,
    FILE_ACCESS_FAILURE,
    MISSING_FLAG,
    NONE
  };

  explicit HuffmanCLIException(const ExceptType type) noexcept;

  const char* what() const noexcept override;

  ExceptType getType() const noexcept;

private:
  ExceptType type_ = NONE;
};
} // namespace huffman

#endif //HUFFMAN_EXCEPTIONS_H
