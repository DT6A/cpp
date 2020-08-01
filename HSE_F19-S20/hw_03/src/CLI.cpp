#include <cassert>
#include <fstream>
#include <iostream>

#include "CLI.h"
#include "HuffmanExceptions.h"
#include "HuffmanArchiver.h"

using namespace huffman;

CLI::CLI(int argc, const char *argv[])
{
  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];

    if (arg == "-c")
      mode_ = COMPRESS;
    else if (arg == "-u")
      mode_ = EXTRACT;
    else if (arg == "-f" || arg == "--file")
    {
      ++i;
      if (i >= argc)
        throw HuffmanCLIException(HuffmanCLIException::MISSING_FLAG);
      inFileName_ = argv[i];
    }
    else if (arg == "-o" || arg == "--output")
    {
      ++i;
      if (i >= argc)
        throw HuffmanCLIException(HuffmanCLIException::MISSING_FLAG);
      outFileName_ = argv[i];
    }
    else
      throw HuffmanCLIException(HuffmanCLIException::INVALID_FLAGS);
  }

  if (inFileName_.empty())
    throw HuffmanCLIException(HuffmanCLIException::UNDEFINED_INPUT_FILE);
  if (outFileName_.empty())
    throw HuffmanCLIException(HuffmanCLIException::UNDEFINED_OUTPUT_FILE);
  if (mode_ == UNDEFINED)
    throw HuffmanCLIException(HuffmanCLIException::UNDEFINED_CLI_MODE);
}

void CLI::run()
{
  assert(mode_ != UNDEFINED);
  assert(!inFileName_.empty());
  assert(!outFileName_.empty());

  std::ifstream input(inFileName_, std::ios::binary);
  if (!input)
    throw HuffmanCLIException(HuffmanCLIException::FILE_ACCESS_FAILURE);
  std::ofstream output(outFileName_, std::ios::binary);
  if (!output)
    throw HuffmanCLIException(HuffmanCLIException::FILE_ACCESS_FAILURE);

  input.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  output.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  HuffmanArchiver archiver = HuffmanArchiver(input, output);

  if (mode_ == COMPRESS)
  {
    HuffmanArchiver::FileStats stats = archiver.compress();

    std::cout << stats.extractedSize << '\n'
              << stats.compressedSize << '\n'
              << stats.extraDataSize << '\n';
  }
  else if (mode_ == EXTRACT)
  {
    HuffmanArchiver::FileStats stats = archiver.extract();

    std::cout << stats.compressedSize << '\n'
              << stats.extractedSize << '\n'
              << stats.extraDataSize << '\n';
  }
}

std::string CLI::getInputFileName() noexcept
{
  return inFileName_;
}

std::string CLI::getOutputFileName() noexcept
{
  return outFileName_;
}

CLI::ArchiverMode CLI::getMode() const noexcept
{
  return mode_;
}