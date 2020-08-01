#include <sstream>
#include <string>
#include <vector>
#include <random>

#include "doctest.h"

#include "StreamManips.h"

using namespace huffman;

TEST_CASE("uint16 writing")
{
  SUBCASE("Two characters")
  {
    std::stringstream oS;

    writeUint16(oS, 'B' << 8 | 'A');
    CHECK(oS.str() == "AB");
  }

  SUBCASE("Three characters and zero")
  {
    std::stringstream oS;

    writeUint16(oS, 'Y' << 8 | 'X');
    writeUint16(oS, 'Z');
    CHECK(oS.str() == std::string("XYZ") + '\0');
  }

  SUBCASE("Binary data")
  {
    std::stringstream oS;
    const int dataSize = 6;
    const char data[dataSize] = {19, 29, 30, 61, 2, 39};

    for (int i = 0; i < dataSize; i += 2)
      writeUint16(oS, data[i + 1] << 8 | data[i]);

    for (char i : data)
      CHECK(oS.get() == i);
  }
}

TEST_CASE("uint16 reading")
{
  SUBCASE("Two characters")
  {
    std::stringstream iS;

    iS.put('A');
    iS.put('B');

    CHECK(readUint16(iS) == ('B' << 8 | 'A'));
  }

  SUBCASE("Three characters and zero")
  {
    std::stringstream iS;

    iS.put('X');
    iS.put('Y');
    iS.put('Z');
    iS.put('\0');

    CHECK(readUint16(iS) == ('Y' << 8 | 'X'));
    CHECK(readUint16(iS) == 'Z');
  }

  SUBCASE("Binary data")
  {
    std::stringstream iS;
    const int dataSize = 6;
    const char data[dataSize] = {19, 29, 30, 61, 2, 39};

    iS.write(data, dataSize);

    for (int i = 0; i < dataSize; i += 2)
      CHECK(readUint16(iS) == (data[i + 1] << 8 | data[i]));
  }
}

TEST_CASE("uint64 writing")
{
  SUBCASE("Eight characters")
  {
    std::stringstream oS;

    writeUint64(oS,
                static_cast<uint64_t>('H') << 56 | static_cast<uint64_t>('G') << 48 |
                static_cast<uint64_t>('F') << 40 | static_cast<uint64_t>('E') << 32 |
                'D' << 24 | 'C' << 16 | 'B' << 8 | 'A');
    CHECK(oS.str() == "ABCDEFGH");
  }

  SUBCASE("Binary data")
  {
    std::stringstream oS;
    const int dataSize = 8;
    const uint8_t data[dataSize] = {19, 29, 30, 61, 2, 39, 17, 81};

    writeUint64(oS, *(reinterpret_cast<const uint64_t *>(&data)));

    for (char i : data)
      CHECK(oS.get() == i);
  }
}

TEST_CASE("uint64 reading")
{
  SUBCASE("Eight characters")
  {
    std::stringstream iS;

    iS.write("ABCDEFGH", 8);

    CHECK(readUint64(iS) == (static_cast<uint64_t>('H') << 56 | static_cast<uint64_t>('G') << 48 |
                             static_cast<uint64_t>('F') << 40 | static_cast<uint64_t>('E') << 32 |
                             'D' << 24 | 'C' << 16 | 'B' << 8 | 'A'));
  }

  SUBCASE("Binary data")
  {
    std::stringstream iS;
    const int dataSize = 8;
    const char data[dataSize] = {19, 29, 30, 61, 2, 39, 23, 25};

    iS.write(data, dataSize);

    CHECK(readUint64(iS) == (static_cast<uint64_t>(data[7]) << 56 | static_cast<uint64_t>(data[6]) << 48 |
                             static_cast<uint64_t>(data[5]) << 40 | static_cast<uint64_t>(data[4]) << 32 |
                             data[3] << 24 | data[2] << 16 | data[1] << 8 | data[0]));
  }
}

TEST_CASE("Non-procedure tests of bit manipulations")
{
  std::stringstream oS;

  SUBCASE("Writing one byte")
  {
    {
      BitWriter bw(oS);

      bw.writeBit(1);
      bw.writeBit(0);
      bw.writeBit(1);
      bw.writeBit(0);
      bw.writeBit(1);
    }
    CHECK(oS.get() == 0b10101000);
  }
  SUBCASE("Writing two bytes")
  {
    {
      BitWriter bw(oS);

      bw.writeBit(1);
      bw.writeBit(0);
      bw.writeBit(1);
      bw.writeBit(0);
      bw.writeBit(1);
      bw.writeBit(0);
      bw.writeBit(0);
      bw.writeBit(0);

      bw.writeBit(1);
      bw.writeBit(1);
      bw.writeBit(1);
      bw.writeBit(1);
      bw.writeBit(0);
      bw.writeBit(1);
    }
    CHECK(oS.get() == 0b10101000);
    CHECK(oS.get() == 0b11110100);
  }

  std::stringstream iS;
  SUBCASE("Reading one byte")
  {
    iS.put(0b11100110);
    {
      BitReader br(iS);

      CHECK(br.readBit() == 1);
      CHECK(br.readBit() == 1);
      CHECK(br.readBit() == 1);
      CHECK(br.readBit() == 0);
      CHECK(br.readBit() == 0);
      CHECK(br.readBit() == 1);
      CHECK(br.readBit() == 1);
      CHECK(br.readBit() == 0);
    }
  }
  SUBCASE("Reading two bytes")
  {
    iS.put(0b11100110);
    iS.put(0b10111001);
    {
      BitReader br(iS);

      CHECK(br.readBit() == 1);
      CHECK(br.readBit() == 1);
      CHECK(br.readBit() == 1);
      CHECK(br.readBit() == 0);
      CHECK(br.readBit() == 0);
      CHECK(br.readBit() == 1);
      CHECK(br.readBit() == 1);
      CHECK(br.readBit() == 0);

      CHECK(br.readBit() == 1);
      CHECK(br.readBit() == 0);
      CHECK(br.readBit() == 1);
      CHECK(br.readBit() == 1);
      CHECK(br.readBit() == 1);
      CHECK(br.readBit() == 0);
      CHECK(br.readBit() == 0);
      CHECK(br.readBit() == 1);
    }
  }
}

TEST_CASE("Procedure bit writing manips tests")
{
  std::stringstream oS;
  std::vector<char> content, output;
  const int testSize = 517, align = 3;

  std::default_random_engine generator(42);
  std::uniform_int_distribution<unsigned char> distribution(0, 1);

  for (int i = 0; i < testSize; ++i)
    content.push_back(distribution(generator));

  {
    BitWriter writer(oS);
    for (auto bit : content)
      writer.writeBit(bit);
  }
  for (int i = 0; i < align; ++i)
    content.push_back(0);

  BitReader reader(oS);

  for (int i = 0; i < testSize + align; ++i)
    output.push_back(reader.readBit());
  CHECK(output == content);
}