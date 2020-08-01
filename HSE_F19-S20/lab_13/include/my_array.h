#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstddef>
#include <stdexcept>

namespace lab_13
{
  template<typename T, std::size_t N>
  class my_array final
  {
  public:
    T & at(std::size_t index);
    const T & at(std::size_t index) const;
    constexpr const T & operator[](std::size_t index) const;
    constexpr T & operator[](std::size_t index);

    constexpr bool empty() const;
    constexpr size_t size() const;
    constexpr void fill(const T &val);

  private:
    T arr_[N];
  };

  template<std::size_t N>
  class my_array<bool, N> final
  {
  private:
    class Proxy_ final
    {
    public:
      constexpr Proxy_(unsigned char *b, const unsigned char biN);
      constexpr Proxy_(Proxy_ &&other);

      constexpr Proxy_ & operator=(const bool value);
      constexpr Proxy_ & operator=(const Proxy_ &other);

      constexpr operator bool() const noexcept;

      unsigned char *byte;
      unsigned char bitNumber;
    };

  public:
    Proxy_ at(std::size_t index);
    bool at(std::size_t index) const;
    constexpr bool operator[](std::size_t index) const;
    constexpr Proxy_ operator[](std::size_t index);

    constexpr bool empty() const;
    constexpr size_t size() const;
    constexpr void fill(const bool val); // No point to create ref

  private:
    unsigned char arr_[N / 8 + (N % 8 == 0 ? 0 : 1)];
  };

  void throwAccessViolationException(size_t index, size_t N);
}  // namespace lab_13

#include "my_array_impl.h"

#endif  // MY_ARRAY_H_