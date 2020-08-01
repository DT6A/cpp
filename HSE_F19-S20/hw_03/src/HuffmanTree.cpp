#include <queue>
#include <algorithm>
#include <cassert>

#include "HuffmanExceptions.h"
#include "HuffmanTree.h"

namespace huffman
{
HuffmanTree::HuffmanNode::HuffmanNode(char symbol, uint64_t freq) noexcept :
  symbol_{symbol}, count_{freq}, left_{nullptr}, right_{nullptr}
{

}

HuffmanTree::HuffmanNode::HuffmanNode(std::unique_ptr<HuffmanNode> L, std::unique_ptr<HuffmanNode> R) noexcept :
  symbol_{0}, count_{L->count_ + R->count_}, left_{std::move(L)}, right_{std::move(R)}
{

}

char HuffmanTree::HuffmanNode::getSymbol() const noexcept
{
  assert(!left_ && !right_);
  return symbol_;
}

uint64_t HuffmanTree::HuffmanNode::getCount() const noexcept
{
  return count_;
}

HuffmanTree::HuffmanTree(const std::map<char, uint64_t> &table)
{
  std::vector<std::unique_ptr<HuffmanNode>> nodes;

  for (auto &notes : table)
    nodes.push_back(std::make_unique<HuffmanNode>(notes.first, notes.second));

  if (nodes.empty())
  {
    root_ = nullptr;
    return;
  }

  if (nodes.size() == 1)
  {
    root_ = std::move(nodes[0]);
    return;
  }

  std::sort(nodes.begin(), nodes.end(),
          [](const std::unique_ptr<HuffmanNode> &n1, const std::unique_ptr<HuffmanNode> &n2) {
    return n2->getCount() > n1->getCount();
  });

  std::queue<std::unique_ptr<HuffmanNode>> queue1, queue2;

  for (auto &node : nodes)
    queue1.push(std::move(node));

  while (!(queue1.empty() && queue2.size() == 1))
  {
    std::unique_ptr<HuffmanNode> node1 = nullptr, node2 = nullptr;

    if (queue2.empty() || (!queue1.empty() && queue1.front()->getCount() < queue2.front()->getCount()))
    {
      node1 = std::move(queue1.front());
      queue1.pop();
    }
    else
    {
      node1 = std::move(queue2.front());
      queue2.pop();
    }

    if (queue2.empty() || (!queue1.empty() && queue1.front()->getCount() < queue2.front()->getCount()))
    {
      node2 = std::move(queue1.front());
      queue1.pop();
    }
    else
    {
      node2 = std::move(queue2.front());
      queue2.pop();
    }

    queue2.push(std::make_unique<HuffmanNode>(std::move(node1), std::move(node2)));
  }

  root_ = std::move(queue2.front());
}

void HuffmanTree::recursiveWalkWithCodesBuilding(
        const HuffmanNode *currentNode, std::vector<bool> &currentCode,
        std::map<char, std::vector<bool>> &codes)
{
  if (!currentNode->left_ && !currentNode->right_)
  {
    if (!currentCode.empty())
      codes[currentNode->getSymbol()] = currentCode;
    else
      codes[currentNode->getSymbol()] = {1};
  }
  else
  {
    if (currentNode->left_)
    {
      currentCode.push_back(0);
      recursiveWalkWithCodesBuilding(currentNode->left_.get(), currentCode, codes);
      currentCode.pop_back();
    }

    if (currentNode->right_)
    {
      currentCode.push_back(1);
      recursiveWalkWithCodesBuilding(currentNode->right_.get(), currentCode, codes);
      currentCode.pop_back();
    }
  }
}

std::map<char, std::vector<bool>> HuffmanTree::buildCodes() const
{
  std::map<char, std::vector<bool>> codes;
  std::vector<bool> code;

  assert(root_);

  if (root_)
    recursiveWalkWithCodesBuilding(root_.get(), code, codes);

  return codes;
}

char HuffmanTree::getChar(BitReader &reader) const
{
  HuffmanNode *currentNode = root_.get();

  while (currentNode)
  {
    if (!currentNode->left_ && !currentNode->right_)
      return currentNode->getSymbol();
    if (reader.readBit() == 0)
      currentNode = currentNode->left_.get();
    else
      currentNode = currentNode->right_.get();
  }

  throw HuffmanArchiverException(HuffmanArchiverException::CORRUPTED_FILE);
}
} // namespace huffman