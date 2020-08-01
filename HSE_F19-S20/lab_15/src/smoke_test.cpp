#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <array>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>

#include "doctest.h"
#include "linq.hpp"

using namespace linq;

TEST_CASE("-> testing end-to-end only input and output") {
          SUBCASE("--> testing to_vector") {
    std::vector<int> ints = { 1, 2, 1, -1, 100, -100, -2 };
            CHECK(from(ints.begin(), ints.end()).to_vector() == ints);
            CHECK(from(ints.begin(), ints.begin()).to_vector().empty());

    std::vector<std::string> strings = { "abs", "qwerty", "how", "are", "you?" };
            CHECK(from(strings.begin(), strings.end()).to_vector() == strings);
  }

          SUBCASE("--> testing copy_to") {
    std::stringstream output;
    std::vector<int> input = { 10, -10, 100, 1, 0, 2, 99999 };
    from(input.begin(), input.begin() + 4).copy_to(std::ostream_iterator<int>(output));

            CHECK(output.str() == "10-101001");

    from(input.begin(), input.begin()).copy_to(std::ostream_iterator<int>(output));
            CHECK(output.str() == "10-101001");
  }
}

TEST_CASE("-> testing drop") {
          SUBCASE("--> testing single drop") {
    double initial[] = { 1.0, 1.2, -1.0, -100 };
    std::vector<double> expected = { -1.0, -100 };

            CHECK(from(initial, initial + 4).drop(2).to_vector() == expected);
            CHECK(from(expected.begin(), expected.end()).drop(0).to_vector() == expected);
            CHECK(from(expected.begin(), expected.end()).drop(1000).to_vector().empty());
  }

          SUBCASE("--> testing consecutive drops") {
    std::vector<char> initial = { 'a', 'a', 'c', 'c', 'd', 'a' };
    std::vector<char> expected1 = { 'c', 'c', 'd', 'a' };
    std::vector<char> expected2 = { 'c', 'd', 'a' };

            CHECK(from(initial.begin(), initial.end()).drop(2).drop(0).to_vector() == expected1);
            CHECK(from(initial.begin(), initial.end()).drop(0).drop(2).to_vector() == expected1);
            CHECK(from(initial.begin(), initial.end()).drop(1).drop(2).to_vector() == expected2);
            CHECK(from(initial.begin(), initial.end()).drop(2).drop(1).to_vector() == expected2);
  }
}

TEST_CASE("-> testing take") {
          SUBCASE("--> testing single take") {
    std::vector<std::string> initial = { "hello", "world", "help", "me" };
    std::vector<std::string> expected = { "hello", "world" };

            CHECK(from(initial.begin(), initial.end()).take(2).to_vector() == expected);
            CHECK(from(initial.begin(), initial.end()).take(100).to_vector() == initial);
            CHECK(from(initial.begin() + 1, initial.begin() + 1).take(100).to_vector().empty());
  }

          SUBCASE("--> testing consecutive takes") {
    std::vector<int> initial = { 1, 2, 3, 4, 5, 6, 1 };
    std::vector<int> expected1 = { 1, 2, 3 };
    std::vector<int> expected2 = {3, 4, 5, 6};

            CHECK(from(initial.begin(), initial.end()).take(3).take(3).to_vector() == expected1);
            CHECK(from(initial.begin(), initial.end()).take(3).take(0).to_vector().empty());
            CHECK(from(initial.begin(), initial.end()).take(0).take(3).to_vector().empty());
            CHECK(from(initial.begin() + 2, initial.end()).take(100).take(4).to_vector() == expected2);
  }
}

TEST_CASE("-> testing select") {
  std::vector<int> initial = { 1, 0, 0, 100, 16, 3 };
  std::vector<int> expected1 = { 0, -1, -1, 9999, 255, 8 };
  std::vector<double> expected2 = { 1, 0, 0, 10 };

          CHECK(from(initial.begin(), initial.end())
                        .select([](int x) { return x * x - 1; } )
                        .to_vector() == expected1);

          CHECK(from(initial.begin(), initial.begin() + 4)
                        .select<double>([](int x) { return sqrt(x); })
                        .to_vector() == expected2);

  std::stringstream output;
  from(initial.begin(), initial.end()).select([](int x) { return x; }).copy_to(std::ostream_iterator<int>(output));
          CHECK(output.str() == "100100163");
}

TEST_CASE("-> testing until") {
  std::array<int, 5> initial = { -1, 0, 100, 2, 3 };
  std::vector<int> expected = { -1, 0 };
  std::vector<int> initial_vec = { -1, 0, 100, 2, 3 };

          CHECK(from(initial.begin(), initial.end())
                        .until([](int x) { return x > 10; })
                        .to_vector() == expected);

          CHECK(from(initial.begin(), initial.end())
                        .until([](int x) { return x < 0; } )
                        .to_vector().empty());

          CHECK(from(initial.begin(), initial.end()).until([](int) { return false; }).to_vector() == initial_vec);
          CHECK(from(initial.begin(), initial.end()).until([](int) { return true; }).to_vector().empty());

  std::vector<int> empty = {};
  from(empty.begin(), empty.end()).until([](int x) { static_cast<void>(x); return false;});
  from(empty.begin(), empty.end()).until([](int x) { static_cast<void>(x); return true;});
}

TEST_CASE("-> testing until_eq") {
  std::vector<int> initial = { -1, 0, -1, 0, 100, 10, 10, 3 };
  std::vector<int> expected = { -1, 0, -1, 0, 100 };
  auto res = from(initial.begin(), initial.end()).until_eq(10).to_vector();
  CHECK(res == expected);
}

TEST_CASE("-> testing where") {
  std::vector<double> initial1 = { 100, 2, 3, 100, 3, 2, 10 };
  std::vector<double> expected1 = { 2, 3, 3, 2, 10 };

          CHECK(from(initial1.begin(), initial1.end())
                        .where([](double x) { return sqrt(x) < 5; } )
                        .to_vector() == expected1);

  std::vector<std::string> initial2 = { "hello", "please", "save", "me", "from", "this" };
  std::vector<std::string> expected2 = { "save", "me", "from", "this" };

          CHECK(from(initial2.begin(), initial2.end())
                        .where([](std::string str) { return str.length() <= 4; } )
                        .to_vector() == expected2);

          CHECK(from(initial2.begin(), initial2.end())
                        .where([](std::string str) { return str[0] == 'b'; } )
                        .to_vector().empty());
}

TEST_CASE("-> testing where_eq") {
  std::vector<int> initial = { 1, 2, 1, 2, 3, 4, 2, 1 };
  std::vector<int> expected = { 2, 2, 3, 4, 2 };

          CHECK(from(initial.begin(), initial.end()).where_neq(1).to_vector() == expected);
          CHECK(from(initial.begin(), initial.end()).where_neq(5).to_vector() == initial);
}

TEST_CASE("-> testing all") {
          SUBCASE("--> testing the 1th chain") {
    std::vector<int> initial = { 1, 2, -1, 100, 3, 10, 5, 10000, -345 };
    std::stringstream output;

    from(initial.begin(), initial.end())
            .where([](int x) { return x > 0; })
            .select<long long>([](int x) { return x * x; })
            .until([](long long x) { return x > 10000; })
            .select<std::string>([](long long x) { return std::to_string(x) + " "; })
            .copy_to(std::ostream_iterator<std::string>(output));

            CHECK(output.str() == "1 4 10000 9 100 25 ");
  }

          SUBCASE("--> testing the 2nd chain") {
    std::vector<int> initial = { -1, 0, 100, -10, 25, 3 };
    std::vector<int> expected = { -2, 98 };

            CHECK(from(initial.begin(), initial.end())
                          .drop(1)
                          .take(100)
                          .take(4)
                          .select([](int x) { return std::abs(x); })
                          .where_neq(10)
                          .until_eq(25)
                          .select([](int x) { return x - 2; })
                          .to_vector() == expected);
  }

          SUBCASE("--> testing the 3rd chain") {
    std::vector<int> initial = { -1, -1, -2, -3, 101, 1919, 1, 2, 2, 10, 2, 3, 4 };
    std::vector<int> expected = { -2, -2 };

            CHECK(from(initial.begin(), initial.end())
                          .drop(2)
                          .take(10)
                          .where([](int x) { return x % 2 == 0; })
                          .select([](int x) { return -x; } )
                          .until([](int x) { return x < -5; })
                          .take(100)
                          .drop(1)
                          .to_vector() == expected);
  }
}
