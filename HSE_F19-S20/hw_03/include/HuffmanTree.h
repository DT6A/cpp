#ifndef HUFF_TREE_H
#define HUFF_TREE_H

#include <vector>
#include <map>
#include <memory>

#include "StreamManips.h"

namespace huffman
{
class HuffmanTree final
{
private:
  class HuffmanNode final
  {
  public:
    explicit HuffmanNode(char symbol, uint64_t freq) noexcept;

    explicit HuffmanNode(std::unique_ptr<HuffmanNode> L, std::unique_ptr<HuffmanNode> R) noexcept;

    char getSymbol() const noexcept;

    uint64_t getCount() const noexcept;

  private:
    char symbol_;
    uint64_t count_;
  public:
    std::unique_ptr<HuffmanNode> left_, right_;
  };

public:
  explicit HuffmanTree(const std::map<char, uint64_t> &table);

  std::map<char, std::vector<bool>> buildCodes() const;

  char getChar(BitReader &reader) const;

private:
  std::unique_ptr<HuffmanNode> root_;

  static void recursiveWalkWithCodesBuilding(
          const HuffmanNode *currentNode, std::vector<bool> &currentCode,
          std::map<char, std::vector<bool>> &codes);
};
} // namespace huffman

#endif //HUFF_TREE_H
