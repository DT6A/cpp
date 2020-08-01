#ifndef STREAM_MANIPS_H
#define STREAM_MANIPS_H

#include <cstdint>
#include <iosfwd>

namespace huffman
{
void writeUint16(std::ostream &stream, const uint16_t data);

uint16_t readUint16(std::istream &stream);

void writeUint64(std::ostream &stream, const uint64_t data);

uint64_t readUint64(std::istream &stream);

class BitWriter final
{
public:
  explicit BitWriter(std::ostream &output) noexcept;

  ~BitWriter();

  void writeBit(const bool bit);

private:
  char byte_ = 0, bitPos_ = 7;
  std::ostream &stream_;
};

class BitReader final
{
public:
  explicit BitReader(std::istream &input) noexcept;

  bool readBit();

private:
  char byte_ = 0, bitPos_ = -1;
  std::istream &stream_;
};
} // namespace huffman

#endif //STREAM_MANIPS_H
