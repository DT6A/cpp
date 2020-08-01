#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <fstream>

#include "doctest.h"

#include "HuffmanExceptions.h"
#include "HuffmanArchiver.h"

using namespace huffman;

constexpr const size_t BASE_HEADER_SIZE = sizeof(HuffmanArchiver::FILE_SIGNATURE) + sizeof(uint16_t);

TEST_CASE("Create archiver")
{
  std::stringstream inS, oS;

  inS.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  oS.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  HuffmanArchiver(inS, oS);
}

TEST_CASE("Compress empty")
{
  std::stringstream inS, oS;

  inS.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  oS.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  HuffmanArchiver archiver(inS, oS);
  HuffmanArchiver::FileStats stats = archiver.compress();

  CHECK(stats.compressedSize == 0);
  CHECK(stats.extractedSize == 0);
  CHECK(stats.extraDataSize == BASE_HEADER_SIZE);

  CHECK(oS.str() == std::string("HM") + '\0' + '\0');
}

TEST_CASE("Extract empty")
{
  std::stringstream inS, oS;

  inS.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  oS.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  inS.write("HM\0\0", 4);

  HuffmanArchiver archiver(inS, oS);
  HuffmanArchiver::FileStats stats = archiver.extract();

  CHECK(stats.compressedSize == 0);
  CHECK(stats.extractedSize == 0);
  CHECK(stats.extraDataSize == BASE_HEADER_SIZE);
  CHECK(oS.str() == "");
}

TEST_CASE("Extract invalid empty")
{
  std::stringstream inS, oS;

  inS.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  oS.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  HuffmanArchiver archiver(inS, oS);

  CHECK_THROWS_AS(archiver.extract(), std::istream::failure);
}

TEST_CASE("Wrong signature")
{
  std::stringstream inS, oS;

  inS.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  oS.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  inS.write("HW\a\0\n", 5);

  HuffmanArchiver archiver(inS, oS);

  try
  {
    archiver.extract();
    CHECK(false);
  }
  catch (HuffmanArchiverException &e)
  {
    CHECK(e.getType() == HuffmanArchiverException::INVALID_FILE_FORMAT);
  }
}

TEST_CASE("Compress and extract file with one character")
{
  std::stringstream inS, oS1, oS2;

  inS.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  oS1.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  oS2.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  inS.put('A');

  HuffmanArchiver archiver(inS, oS1);
  HuffmanArchiver::FileStats stats = archiver.compress();

  CHECK(stats.compressedSize == 1);
  CHECK(stats.extractedSize == 1);
  CHECK(stats.extraDataSize == BASE_HEADER_SIZE + 1 + sizeof(size_t));

  HuffmanArchiver extracter(oS1, oS2);
  stats = extracter.extract();

  CHECK(stats.compressedSize == 1);
  CHECK(stats.extractedSize == 1);
  CHECK(stats.extraDataSize == BASE_HEADER_SIZE + 1 + sizeof(size_t));

  CHECK(oS2.str() == "A");
}

TEST_CASE("Single character many times")
{
  std::stringstream inS, oS1, oS2;
  const std::string content(303, 'A');

  inS.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  oS1.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  oS2.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  inS.write(content.c_str(), content.size());

  HuffmanArchiver archiver(inS, oS1);
  HuffmanArchiver::FileStats stats = archiver.compress();

  CHECK(stats.compressedSize == 38);
  CHECK(stats.extractedSize == content.size());
  CHECK(stats.extraDataSize == BASE_HEADER_SIZE + 1 + sizeof(size_t));

  HuffmanArchiver extracter(oS1, oS2);
  stats = extracter.extract();

  CHECK(stats.compressedSize == 38);
  CHECK(stats.extractedSize == content.size());
  CHECK(stats.extraDataSize == BASE_HEADER_SIZE + 1 + sizeof(size_t));

  CHECK(oS2.str() == content);
}

TEST_CASE("Huge binary file processing")
{
  std::stringstream inS, oS1, oS2;
  std::string content;

  inS.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  oS1.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  oS2.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  std::default_random_engine generator(42);
  std::uniform_int_distribution<char> distribution(-128,127);

  for (size_t i = 0; i < 1000000; ++i)
    content.push_back(distribution(generator));
  inS.write(content.c_str(), content.size());

  HuffmanArchiver archiver(inS, oS1);
  HuffmanArchiver::FileStats stats = archiver.compress();

  CHECK(stats.extractedSize == content.size());
  CHECK(stats.extraDataSize == BASE_HEADER_SIZE + 256 * (1 + sizeof(size_t)));

  HuffmanArchiver extracter(oS1, oS2);
  stats = extracter.extract();

  CHECK(stats.extractedSize == content.size());
  CHECK(stats.extraDataSize == BASE_HEADER_SIZE + 256 * (1 + sizeof(size_t)));

  CHECK(oS2.str() == content);
}

TEST_CASE("Text file processing")
{
  const std::string text = "There's a voice that keeps on calling me. Down the road, that's where I'll always be. Every stop I make, I make a new friend. Can't stay for long, just turn around and I'm gone again. Maybe tomorrow, I'll want to settle down, Until tomorrow, I'll just keep moving on.";
  std::stringstream inStream, oStream1, oStream2;
  inStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  oStream1.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  oStream2.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  inStream.write(text.c_str(), text.size());

  HuffmanArchiver::FileStats stats;

  HuffmanArchiver archiver(inStream, oStream1);
  stats = archiver.compress();

  CHECK(stats.compressedSize == 148);
  CHECK(stats.extractedSize == text.size());
  CHECK(stats.extraDataSize == BASE_HEADER_SIZE + 34 * (1 + sizeof(size_t)));

  oStream2.clear();
  HuffmanArchiver extracter(oStream1, oStream2);
  stats = extracter.extract();

  CHECK(stats.compressedSize == 148);
  CHECK(stats.extractedSize == text.size());
  CHECK(stats.extraDataSize == BASE_HEADER_SIZE + 34 * (1 + sizeof(size_t)));

  std::vector<char> ov;
  CHECK(oStream2.str() == text);
}
