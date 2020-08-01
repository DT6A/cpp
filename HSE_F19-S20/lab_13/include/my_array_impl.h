#ifndef MY_ARRAY_IMPL_H_
#define MY_ARRAY_IMPL_H_

#include <cstring>
#include <cassert>
#include <string>

namespace lab_13
{
  void throwAccessViolationException(size_t index, size_t N)
  {
    throw std::out_of_range(
            std::string("Trying to access by index ") +
            std::to_string(index) +
            std::string(". But array has size ") +
            std::to_string(N));
  }

  template<typename T, std::size_t N>
  T & my_array<T, N>::at(std::size_t index)
  {
    if (index >= N)
      throwAccessViolationException(index, N);
    return arr_[index];
  }

  template<typename T, std::size_t N>
  const T & my_array<T, N>::at(std::size_t index) const
  {
    if (index >= N)
      throwAccessViolationException(index, N);
    return arr_[index];
  }

  template<typename T, std::size_t N>
  constexpr const T & my_array<T, N>::operator[](std::size_t index) const
  {
    assert(index < N);
    return arr_[index];
  }

  template<typename T, std::size_t N>
  constexpr T & my_array<T, N>::operator[](std::size_t index)
  {
    assert(index < N);
    return arr_[index];
  }

  template<typename T, std::size_t N>
  constexpr bool my_array<T, N>::empty() const
  {
    return N == 0;
  }

  template<typename T, std::size_t N>
  constexpr size_t my_array<T, N>::size() const
  {
    return N;
  }

  template<typename T, std::size_t N>
  constexpr void my_array<T, N>::fill(const T &val)
  {
    for (size_t i = 0; i < N; ++i)
      (*this)[i] = T(val);
  }

  template<std::size_t N>
  constexpr my_array<bool, N>::Proxy_::Proxy_(unsigned char *b, const unsigned char biN)
    : byte{b}, bitNumber{biN}
  {

  }

  template<std::size_t N>
  constexpr my_array<bool, N>::Proxy_::Proxy_(Proxy_ &&other)
    : byte(other.byte), bitNumber{other.bitNumber}
  {
    other.byte = nullptr;
    other.bitNumber = 0;
  }

  template<std::size_t N>
  constexpr auto my_array<bool, N>::Proxy_::operator=(const bool value) -> Proxy_ &
  {
    *byte &= ~(static_cast<unsigned char>(1) << bitNumber);
    *byte |= static_cast<unsigned char>(value) << bitNumber;

    return *this;
  }

  template<std::size_t N>
  constexpr auto my_array<bool, N>::Proxy_::operator=(const Proxy_ &other) -> Proxy_ &
  {
    *this = static_cast<bool>(other);

    return *this;
  }

  template<std::size_t N>
  constexpr my_array<bool, N>::Proxy_::operator bool() const noexcept
  {
    return static_cast<bool>(*byte & (static_cast<unsigned char>(1) << bitNumber));
  }

  template<std::size_t N>
  auto my_array<bool, N>::at(std::size_t index) -> Proxy_
  {
    if (index >= N)
      throwAccessViolationException(index, N);
    return Proxy_(arr_ + index / 8, index % 8);
  }

  template<std::size_t N>
  bool my_array<bool, N>::at(std::size_t index) const
  {
    if (index >= N)
      throwAccessViolationException(index, N);
    return arr_[index / 8] & (static_cast<unsigned char>(1) << index % 8);
  }

  template<std::size_t N>
  constexpr bool my_array<bool, N>::operator[](std::size_t index) const
  {
    assert(index < N);
    return arr_[index / 8] & (static_cast<unsigned char>(1) << index % 8);
  }

  template<std::size_t N>
  constexpr auto my_array<bool, N>::operator[](std::size_t index) -> Proxy_
  {
    assert(index < N);
    return Proxy_(arr_ + index / 8, index % 8);
  }

  template<std::size_t N>
  constexpr bool my_array<bool, N>::empty() const
  {
    return N == 0;
  }

  template<std::size_t N>
  constexpr size_t my_array<bool, N>::size() const
  {
    return N;
  }

  template<std::size_t N>
  constexpr void my_array<bool, N>::fill(const bool val)
  {
    memset(arr_, val ? 255 : 0, sizeof(arr_));
  }
}

#endif //MY_ARRAY_IMPL_H_
