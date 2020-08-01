#include <string>
#include <sstream>

#include "doctest.h"

#include "HuffmanExceptions.h"
#include "HuffmanTree.h"

using namespace huffman;

TEST_CASE("Single character")
{
  for (int c = 0; c < 256; ++c)
  {
    std::map<char, size_t> table;
    table[c] = 1;
    HuffmanTree tree(table);
    std::map<char, std::vector<bool>> codes;
    codes = tree.buildCodes();
    CHECK(codes == std::map<char, std::vector<bool>>{{c, {1}}});

    std::stringstream iS;
    iS.put(1);
    BitReader reader(iS);
    CHECK(static_cast<char>(c) == tree.getChar(reader));
  }
}

TEST_CASE("Different characters and counts have right lengths order")
{
  std::map<char, size_t> table;
  for (int c = 0; c < 256; ++c)
    table[static_cast<char>(c)] = c + 1;
  HuffmanTree tree(table);
  std::map<char, std::vector<bool>> codes;
  codes = tree.buildCodes();
  REQUIRE(codes.size() == 256);
  for (int c = 0; c < 255; ++c)
    CHECK(codes[static_cast<char>(c)].size() >= codes[static_cast<char>(c + 1)].size());
}

TEST_CASE("Two characters")
{
  std::map<char, size_t> table;
  table['A'] = 30;
  table['B'] = 239;
  HuffmanTree tree(table);
  std::map<char, std::vector<bool>> codes;
  codes = tree.buildCodes();

  CHECK(codes == std::map<char, std::vector<bool>>{{'A', {0}}, {'B', {1}}});

  std::stringstream iS;
  iS.put(0b10000000);
  BitReader reader(iS);

  CHECK(tree.getChar(reader) == 'B');
  CHECK(tree.getChar(reader) == 'A');
}

TEST_CASE("Three characters")
{
  std::map<char, size_t> table;
  table['A'] = 30;
  table['B'] = 239;
  table['C'] = 1;
  HuffmanTree tree(table);
  std::map<char, std::vector<bool>> codes;
  codes = tree.buildCodes();

  CHECK(codes == std::map<char, std::vector<bool>>{{'B', {1}}, {'A', {0, 1}}, {'C', {0, 0}}});

  std::stringstream iS;
  iS.put(0b10100000);
  BitReader reader(iS);

  CHECK(tree.getChar(reader) == 'B');
  CHECK(tree.getChar(reader) == 'A');
  CHECK(tree.getChar(reader) == 'C');
}

TEST_CASE("hello world")
{
  std::map<char, size_t> table;
  table['h'] = 1;
  table['e'] = 1;
  table['l'] = 3;
  table['o'] = 2;
  table[' '] = 1;
  table['w'] = 1;
  table['r'] = 1;
  table['d'] = 1;
  HuffmanTree tree(table);
  std::map<char, std::vector<bool>> codes;
  codes = tree.buildCodes();
  REQUIRE(codes.size() == 8);

  size_t compressedSize = 0;
  for (auto note : table)
    compressedSize += note.second * codes[note.first].size();
  CHECK(compressedSize == 32);
}

TEST_CASE("Longer text")
{
  std::string text = "Long long but actually small text!!!";
  std::map<char, size_t> table;
  for (auto c : text)
    table[c]++;
  HuffmanTree tree(table);
  std::map<char, std::vector<bool>> codes;
  codes = tree.buildCodes();
  REQUIRE(codes.size() == 17);
  size_t compressedSize = 0;
  for (auto note : table)
    compressedSize += note.second * codes[note.first].size();
  CHECK(compressedSize == 138);
}
