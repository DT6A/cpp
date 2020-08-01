#include <cstddef>  // std::size_t
#include <string>  // std::string
#include <type_traits>
#include <charconv>
#include <vector>
#include <limits>
#include <cassert>

#if __cplusplus < 201703L
#error At least C++17 is required
#endif

namespace format {
template<typename T, typename Enable = void>
struct FormatHelper {
  static constexpr bool IS_VALID = false;
};

template<typename T, typename std::enable_if_t<FormatHelper<T>::IS_VALID>* = nullptr>
std::string make_string(const T &value) {
  FormatHelper<T> helper(value);  // Explicit!
  std::string formatted;
  formatted.reserve(helper.estimate_size());
  helper.append_to(formatted);
  formatted.shrink_to_fit();
  return formatted;
}

template<>
struct FormatHelper<bool> {

  explicit FormatHelper(bool value) : value_{value}
  {

  }

  std::size_t estimate_size() const
  {
    // 4 is length of "true", 5 is length of "false"
    return value_ ? 4 : 5;
  }

  void append_to(std::string &s) const
  {
    s += value_ ? "true" : "false";
  }

  static constexpr bool IS_VALID = true;

private:
  bool value_;
};

template<typename T>
struct FormatHelper<T, std::enable_if_t<std::is_integral_v<T>>> {
  explicit FormatHelper(T value) : value_{value}
  {

  }

  std::size_t estimate_size() const
  {
    return MAX_DECIMAL_LENGTH;
  }

  void append_to(std::string &s) const
  {
    char buffer[MAX_DECIMAL_LENGTH] = {};
    auto [p, ec] = std::to_chars(std::begin(buffer), std::end(buffer), value_);

    assert(ec == std::errc());
    s += std::string_view(buffer, p - buffer);
  }

  static constexpr bool IS_VALID = true;

private:
  T value_;
  /* + 1 because digits10 gives number of digits that can be represented without loss,
   * for example std::numeric_limits<unsigned char>::digits10 is equal to 2 because number 256 or bigger can't be stored in unsigned char.
   */
  static constexpr std::size_t MAX_DECIMAL_LENGTH = std::numeric_limits<T>::digits10 + std::numeric_limits<T>::is_signed + 1;
};

template<typename T>
struct FormatHelper<T, std::enable_if_t<std::is_same_v<decltype(std::declval<const T &>().format()), std::string>>> {
  static constexpr std::size_t FORMAT_LENGTH_ESTIMATE = 10;

  explicit FormatHelper(const T &value) : value_{value}
  {

  }

  std::size_t estimate_size() const
  {
    return FORMAT_LENGTH_ESTIMATE;
  }

  void append_to(std::string &s) const
  {
    s += value_.format();
  }

  static constexpr bool IS_VALID = true;

private:
  const T &value_;
};

template<typename T>
struct FormatHelper<std::vector<T>, std::enable_if_t<FormatHelper<T>::IS_VALID>> {
  explicit FormatHelper(const std::vector<T> &value) : value_{value}
  {
    // 2 * for spaces and commas, - 1 for redundant space and comma after the last element and + 2 for opening and closing brackets
    size_ = 2 * (value.size() > 0 ? value.size() - 1 : 0) + 2;
    for (const auto &el : value)
      size_ += FormatHelper<T>(el).estimate_size();
  }

  std::size_t estimate_size() const
  {
    return size_;
  }

  void append_to(std::string &s) const
  {
    s += '{';
    for (std::size_t i = 0; i + 1 < value_.size(); ++i)
    {
      s += make_string(static_cast<const T&>(value_[i]));
      s += ", ";
    }
    if (value_.size() > 0)
      s += make_string(static_cast<const T&>(value_[value_.size() - 1]));
    s += '}';
  }

  static constexpr bool IS_VALID = true;

private:
  const std::vector<T> &value_;
  std::size_t size_;
};
}  // namespace format
