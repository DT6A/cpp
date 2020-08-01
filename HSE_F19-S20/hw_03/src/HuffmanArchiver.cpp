#include <fstream>
#include <stdexcept>

#include "HuffmanExceptions.h"
#include "HuffmanArchiver.h"

namespace huffman
{
HuffmanArchiver::HuffmanArchiver(std::istream &input, std::ostream &output) noexcept :
        inFile{input}, outFile{output}
{

}

HuffmanArchiver::FileStats HuffmanArchiver::compress()
{
  std::map<char, uint64_t> frequenciesTable;
  std::map<char, std::vector<bool>> codes;

  countFrequencies(frequenciesTable);

  HuffmanTree tree(frequenciesTable);

  if (frequenciesTable.size() > 0)
    codes = tree.buildCodes();

  FileStats stats;
  stats.extractedSize = countDecompressedSize(frequenciesTable);
  stats.compressedSize = countCompressedSize(frequenciesTable, codes);
  stats.extraDataSize = writeHeader(frequenciesTable);
  writeCompressedData(codes);

  return stats;
}

HuffmanArchiver::FileStats HuffmanArchiver::extract()
{
  std::map<char, uint64_t> frequenciesTable;
  std::map<char, std::vector<bool>> codes;
  FileStats stats;
  uint64_t decompressedSize = 0;

  stats.extraDataSize = readHeader(frequenciesTable);

  HuffmanTree tree(frequenciesTable);

  if (stats.extraDataSize != sizeof(FILE_SIGNATURE) + sizeof(uint16_t))
  {
    codes = tree.buildCodes();
    decompressedSize = countDecompressedSize(frequenciesTable);
  }

  BitReader reader(inFile);
  for (uint64_t counter = 0; counter < decompressedSize; ++counter)
  {
    char nextChar = tree.getChar(reader);

    outFile.write(&nextChar, 1);
  }

  stats.compressedSize = countCompressedSize(frequenciesTable, codes);
  stats.extractedSize = decompressedSize;

  return stats;
}

void HuffmanArchiver::countFrequencies(std::map<char, uint64_t> &table)
{
  inFile.clear();
  inFile.seekg(0);

  char byte;
  while (inFile.peek() != EOF)
  {
    inFile.read(&byte, 1);
    table[byte]++;
  }
}

void HuffmanArchiver::writeCompressedData(std::map<char, std::vector<bool>> &codes)
{
  inFile.clear();
  inFile.seekg(0);

  char symb;
  BitWriter writer(outFile);
  while (inFile.peek() != EOF)
  {
    inFile.read(&symb, 1);
    for (int bit : codes[symb])
      writer.writeBit(bit);
  }
}

uint64_t HuffmanArchiver::countCompressedSize(
        std::map<char, uint64_t> &table, std::map<char, std::vector<bool>> &codes)
{
  uint64_t cnt = 0;

  for (const auto &note : table)
    cnt += note.second * codes[note.first].size();

  return cnt / 8 + ((cnt % 8 != 0) ? 1 : 0);
}

uint64_t HuffmanArchiver::countDecompressedSize(std::map<char, uint64_t> &table)
{
  uint64_t cnt = 0;

  for (const auto &note : table)
    cnt += note.second;

  return cnt;
}

uint64_t HuffmanArchiver::writeHeader(const std::map<char, uint64_t> &table)
{
  writeUint16(outFile, FILE_SIGNATURE);
  writeUint16(outFile, static_cast<uint16_t>(table.size()));

  for (auto &note : table)
  {
    outFile.write(&note.first, 1);
    writeUint64(outFile, note.second);
  }

  return sizeof(FILE_SIGNATURE) + sizeof(uint16_t) + table.size() * (sizeof(uint64_t) + 1);
}

uint64_t HuffmanArchiver::readHeader(std::map<char, uint64_t> &table)
{
  uint16_t signature = readUint16(inFile);

  if (signature != FILE_SIGNATURE)
    throw HuffmanArchiverException(HuffmanArchiverException::ExceptType::INVALID_FILE_FORMAT);

  uint16_t numberOfElements = readUint16(inFile);

  for (uint16_t i = 0; i < numberOfElements; ++i)
  {
    char symbol;

    inFile.read(&symbol, 1);
    table[symbol] = readUint64(inFile);
  }

  return sizeof(FILE_SIGNATURE) + sizeof(uint16_t) + numberOfElements * (sizeof(uint64_t) + 1);
}
} // namespace huffman

