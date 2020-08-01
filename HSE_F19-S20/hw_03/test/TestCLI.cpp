#include <string>

#include "doctest.h"

#include "HuffmanExceptions.h"
#include "CLI.h"

using namespace huffman;

TEST_CASE("Invalid flags")
{
  SUBCASE("All incorrect")
  {
    const char *flags[] = {"proc", "flag", "flag", "another", "one", "flag"};

    CHECK_THROWS_AS(CLI(6, flags), HuffmanCLIException);
  }

  SUBCASE("Last incorrect")
  {
    const char *flags[] = {"proc", "-u", "-f", "name", "-c", "flag"};

    CHECK_THROWS_AS(CLI(6, flags), HuffmanCLIException);
  }

  SUBCASE("Additional incorrect")
  {
    const char *flags[] = {"proc", "-u", "-f", "name", "-c", "-u", "flag"};
    CHECK_THROWS_AS(CLI(7, flags), HuffmanCLIException);
  }
}

TEST_CASE("No file name after the file flag")
{
  const char *flags[] = {"proc", "-u", "-o", "name", "-u", "-f"};
  SUBCASE("-f")
  {
    CHECK_THROWS_AS(CLI(6, flags), HuffmanCLIException);
  }

  SUBCASE("--file")
  {
    flags[5] = "--file";
    CHECK_THROWS_AS(CLI(6, flags), HuffmanCLIException);
  }

  SUBCASE("-o")
  {
    flags[5] = "-o";
    CHECK_THROWS_AS(CLI(6, flags), HuffmanCLIException);
  }

  SUBCASE("--output")
  {
    flags[5] = "--output";
    CHECK_THROWS_AS(CLI(6, flags), HuffmanCLIException);
  }
}

TEST_CASE("Undefined flags")
{
  SUBCASE("Mode")
  {
    const char *flags[] = {"proc", "-o", "name", "--output", "name", "-f", "name"};
    CHECK_THROWS_AS(CLI(7, flags), HuffmanCLIException);
  }

  SUBCASE("In file")
  {
    const char *flags[] = {"proc", "-o", "name", "--output", "name", "-c"};
    CHECK_THROWS_AS(CLI(6, flags), HuffmanCLIException);
  }

  SUBCASE("Out file")
  {
    const char *flags[] = {"proc", "-f", "name", "--file", "name", "-u"};
    CHECK_THROWS_AS(CLI(6, flags), HuffmanCLIException);
  }
}
TEST_CASE("Correct flags")
{
  SUBCASE("Usual usage")
  {
    const char *flags[] = {"proc", "-c", "-o", "name", "-f", "name2"};
    CLI cli(6, flags);
    CHECK(cli.getMode() == CLI::ArchiverMode::COMPRESS);
    CHECK(std::string("name") == cli.getOutputFileName());
    CHECK(std::string("name2") == cli.getInputFileName());
  }
  SUBCASE("Reverse")
  {
    const char *flags[] = {"proc", "-f", "name", "-o", "name2", "-u"};
    CLI cli(6, flags);
    CHECK(cli.getMode() == CLI::ArchiverMode::EXTRACT);
    CHECK(std::string("name2") == cli.getOutputFileName());
    CHECK(std::string("name") == cli.getInputFileName());
  }
  SUBCASE("Long names")
  {
    const char *flags[] = {"proc", "--output", "name", "--file", "name2", "-c"};
    CLI cli(6, flags);
    CHECK(cli.getMode() == CLI::ArchiverMode::COMPRESS);
    CHECK(std::string("name") == cli.getOutputFileName());
    CHECK(std::string("name2") == cli.getInputFileName());
  }
  SUBCASE("Mix")
  {
    const char *flags[] = {"proc", "--output", "name", "-f", "name2", "-u"};
    CLI cli(6, flags);
    CHECK(cli.getMode() == CLI::ArchiverMode::EXTRACT);
    CHECK(std::string("name") == cli.getOutputFileName());
    CHECK(std::string("name2") == cli.getInputFileName());
  }
  SUBCASE ("Extra arguments")
  {
    const char *flags[] = {"proc", "--output", "name", "-f", "name2", "-u", "-o", "name3", "--file", "name4", "-c"};
    CLI cli(11, flags);
    CHECK(cli.getMode() == CLI::ArchiverMode::COMPRESS);
    CHECK(std::string("name3") == cli.getOutputFileName());
    CHECK(std::string("name4") == cli.getInputFileName());
  }
}