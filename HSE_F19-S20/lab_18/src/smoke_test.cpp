#include "format.hpp"

#include <string>
#include <vector>
#include <functional>
#include <experimental/type_traits>
#include <iostream>
#include <climits>

#include <doctest.h>
#include <boost/hana.hpp>

#define TEST_BOOL
#define TEST_SFINAE
#define TEST_VECTOR
#define TEST_VECTOR_SFINAE
#define TEST_INTEGRAL
#define TEST_FORMAT_MEMBER
#define TEST_FORMAT_MEMBER_SFINAE

auto is_formattable = boost::hana::is_valid(
    [](const auto &value)
        -> std::void_t<decltype(format::make_string(value))> {
    }
);

#ifdef TEST_BOOL
TEST_CASE("bool") {
    CHECK(format::make_string(true) == "true");
    CHECK(format::make_string(false) == "false");
    static_assert(is_formattable(true));  // Follows previous lines' compilation.
    static_assert(is_formattable(false));
}
#endif

#ifdef TEST_SFINAE
TEST_CASE("Non-formattable") {
    struct {} s;
    CHECK(!is_formattable(s));  // Not static_assert so it's not a compilation error.
    //format::make_string(s);  // Should not compile with a short error.
}
#endif

#ifdef TEST_INTEGRAL
TEST_SUITE("integral") {
TEST_CASE("int") {
    static_assert(is_formattable(0));
    CHECK(format::make_string(0) == "0");
    CHECK(format::make_string(12345) == "12345");
    CHECK(format::make_string(-12345) == "-12345");
    CHECK(format::make_string(-0) == "0");
    CHECK(format::make_string(LLONG_MIN) == "-9223372036854775808");
    CHECK(format::make_string(LLONG_MAX) == "9223372036854775807");
    CHECK(format::make_string(ULLONG_MAX) == "18446744073709551615");
    CHECK(format::make_string(INT_MAX) == "2147483647");
    CHECK(format::make_string(INT_MIN) == "-2147483648");
    CHECK(format::make_string((char) CHAR_MAX) == "127");
    CHECK(format::make_string((char) CHAR_MIN) == "-128");
    //CHECK(format::make_string(-9223372036854775808) == "-9223372036854775808");
}

TEST_CASE("unsigned int") {
    CHECK(format::make_string(0u) == "0");
    CHECK(format::make_string(12345u) == "12345");
}
}
#endif

#ifdef TEST_VECTOR
TEST_SUITE("vector<T>") {
#ifdef TEST_BOOL
TEST_CASE("T=bool") {
    CHECK(format::make_string(std::vector<bool>{}) == "{}");
    CHECK(format::make_string(std::vector{true}) == "{true}");
    CHECK(format::make_string(std::vector{false}) == "{false}");
    CHECK(format::make_string(std::vector{true, false, true, true}) == "{true, false, true, true}");
}
TEST_CASE("T=vector<bool>") {
    CHECK(format::make_string(std::vector<std::vector<bool>>{}) == "{}");
    CHECK(format::make_string(std::vector{
        std::vector{true, false},
        std::vector<bool>{},
        std::vector{true}
    }) == "{{true, false}, {}, {true}}");
}
#endif
#ifdef TEST_INTEGRAL
TEST_CASE("T=int") {
    CHECK(format::make_string(std::vector<int>{}) == "{}");
    CHECK(format::make_string(std::vector{10}) == "{10}");
    CHECK(format::make_string(std::vector{-10, 20, -5}) == "{-10, 20, -5}");
}
#endif
#ifdef TEST_VECTOR_SFINAE
TEST_CASE("T is non-formattable") {
    struct S {};
    std::vector<S> vec(10);
    CHECK(!is_formattable(vec));  // Not static_assert so it's not a compilation error.
    //format::make_string(vec);  // Should not compile with a short error.
}
#endif
}
#endif

#ifdef TEST_FORMAT_MEMBER
TEST_SUITE(".format() member") {
struct S {
    std::string format() const { return "0123456789"; }
};

struct Base {
   virtual std::string format() const { return "Base"; }
};

struct Derived : Base {
  std::string format() const override { return "Derived"; }
};

struct Derived2 : public Base {
  std::string format() { return "Derived2"; }
  std::string format() const override { return "Overrided"; }
};

TEST_CASE("Formatted") {
    CHECK(format::make_string(S{}) == "0123456789");
}

TEST_CASE("Inheritance") {
    CHECK(format::make_string(Base{}) == "Base");
    CHECK(format::make_string(Derived{}) == "Derived");

    Base *obj = new Derived();
    CHECK(format::make_string(*obj) == "Derived");

    obj = new Derived2();
    CHECK(format::make_string(*obj) == "Overrided");
}
#ifdef TEST_VECTOR
TEST_CASE("vector<T>") {
    std::vector<S> vec(2);
    CHECK(format::make_string(vec) == "{0123456789, 0123456789}");
}
#endif
}
#endif

#ifdef TEST_FORMAT_MEMBER_SFINAE
TEST_SUITE("bad .format() member") {
TEST_CASE("Non-const qualified") {
    struct {
        std::string format() { return "hello"; }
    } s;
    CHECK(!is_formattable(s));
}
TEST_CASE("Rvalue-ref-qualified") {
    struct {
        std::string format() && { return "hello"; }
    } s;
    CHECK(!is_formattable(s));
}
TEST_CASE("Returns non-std::string") {
    struct {
        int format() const { return 10; }
    } s;
    CHECK(!is_formattable(s));
}
  TEST_CASE("Takes param") {
    struct {
      std::string format(int s) const { s++; return "KekW"; }
    } s;
            CHECK(!is_formattable(s));
  }
}
#endif

