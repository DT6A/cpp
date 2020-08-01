#ifndef HUFFMAN_ARCHIVER_H
#define HUFFMAN_ARCHIVER_H

#include <cstddef>
#include <memory>
#include <iosfwd>
#include <map>
#include <vector>

#include "HuffmanTree.h"

namespace huffman
{
class HuffmanArchiver final
{
public:
  constexpr static inline uint16_t FILE_SIGNATURE = 0x4D48;

  struct FileStats final
  {
    uint64_t compressedSize = 0, extractedSize = 0, extraDataSize = 0;
  };

  explicit HuffmanArchiver(std::istream &input, std::ostream &output) noexcept;

  FileStats compress();

  FileStats extract();

private:
  std::istream &inFile;
  std::ostream &outFile;

  void countFrequencies(std::map<char, uint64_t> &table);

  void writeCompressedData(std::map<char, std::vector<bool>> &codes);

  static uint64_t countCompressedSize(
          std::map<char, uint64_t> &table, std::map<char, std::vector<bool>> &codes);

  static uint64_t countDecompressedSize(std::map<char, uint64_t> &table);

  uint64_t writeHeader(const std::map<char, uint64_t> &table);

  uint64_t readHeader(std::map<char, uint64_t> &table);
};
} // namespace huffman

#endif //HUFFMAN_ARCHIVER_H
