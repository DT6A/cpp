#include <cassert>

#include "HuffmanExceptions.h"

namespace huffman
{
HuffmanArchiverException::HuffmanArchiverException(const ExceptType type) noexcept : type_{type}
{

}

const char * HuffmanArchiverException::what() const noexcept
{
  switch(type_)
  {
    case INVALID_FILE_FORMAT:
      return "Trying to extract file with wrong format.";
    case CORRUPTED_FILE:
      return "Failed to extract file. Probably file is damaged.";
    default:
      assert(false);
  }
}

HuffmanArchiverException::ExceptType HuffmanArchiverException::getType() const noexcept
{
  return type_;
}

HuffmanCLIException::HuffmanCLIException(const ExceptType type) noexcept : type_{type}
{

}

const char * HuffmanCLIException::what() const noexcept
{
  switch(type_)
  {
    case INVALID_FLAGS:
      return "Invalid flags. Usage: hw_03 MODE -f INPUT FILE -o OUTPUT FILE";
    case UNDEFINED_INPUT_FILE:
      return "Input file wasn't specified";
    case UNDEFINED_OUTPUT_FILE:
      return "Output file wasn't specified";
    case UNDEFINED_CLI_MODE:
      return "Archiver mode wasn't specified";
    case FILE_ACCESS_FAILURE:
      return "Failed to read/write file.";
    case MISSING_FLAG:
      return "Missing file name after -f, --file, -o or --output flag";
    default:
      assert(false);
  }
}

HuffmanCLIException::ExceptType HuffmanCLIException::getType() const noexcept
{
  return type_;
}
} // namespace huffman