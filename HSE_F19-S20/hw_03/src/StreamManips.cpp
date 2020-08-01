#include <iostream>

#include "HuffmanExceptions.h"
#include "StreamManips.h"

namespace huffman
{
void writeUint16(std::ostream &stream, const uint16_t data)
{
  char byte = data & 0xFF;

  stream.write(&byte, 1);
  byte = (data >> 8) & 0xFF;
  stream.write(&byte, 1);
}

uint16_t readUint16(std::istream &stream)
{
  char byte = 0;
  uint16_t data = 0;

  stream.read(&byte, 1);
  data |= static_cast<unsigned char>(byte);
  stream.read(&byte, 1);
  data |= static_cast<unsigned char>(byte) << 8;

  return data;
}

void writeUint64(std::ostream &stream, const uint64_t data)
{
  for (int i = 0; i < 4; ++i)
    writeUint16(stream, (data >> i * 16) & 0xFFFF);
}

uint64_t readUint64(std::istream &stream)
{
  uint64_t data = 0;

  for (uint64_t i = 0; i < 4; ++i)
    data |= static_cast<uint64_t>(readUint16(stream)) << (i * 16);

  return data;
}

BitWriter::BitWriter(std::ostream &output) noexcept : stream_{output}
{

}

BitWriter::~BitWriter()
{
  if (bitPos_ < 7)
    stream_.write(&byte_, 1);
}

void BitWriter::writeBit(const bool bit)
{
  byte_ |= bit << bitPos_;
  bitPos_--;

  if (bitPos_ < 0)
  {
    stream_.write(&byte_, 1);
    byte_ = 0;
    bitPos_ = 7;
  }
}

BitReader::BitReader(std::istream &input) noexcept : stream_{input}
{

}

bool BitReader::readBit()
{
  if (bitPos_ < 0)
  {
    if (!stream_)
      throw HuffmanArchiverException(HuffmanArchiverException::CORRUPTED_FILE);
    stream_.read(&byte_, 1);
    bitPos_ = 7;
  }
  char bit = (byte_ >> bitPos_) & 1;
  bitPos_--;
  return bit;
}
} // namespace huffman
