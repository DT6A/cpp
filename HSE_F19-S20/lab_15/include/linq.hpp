#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>
#include <iterator>
#include <cassert>

namespace linq {
namespace impl {

template<typename T, typename Iter>
class range_enumerator;
template<typename T>
class drop_enumerator;
template<typename T>
class take_enumerator;
template<typename T, typename U, typename F>
class select_enumerator;
template<typename T, typename F>
class until_enumerator;
template<typename T, typename F>
class where_enumerator;

template<typename T>
class enumerator {
public:

  enumerator() = default;

  virtual T operator*() noexcept = 0;

  virtual void operator++() = 0;

  virtual explicit operator bool() noexcept = 0;

  enumerator(const enumerator<T> &) = delete;
  enumerator(enumerator<T> &&) = delete;

  enumerator & operator=(const enumerator<T> &) = delete;
  enumerator & operator=(enumerator<T> &&) = delete;

  virtual ~enumerator() = default;

  auto drop(int count) && noexcept {
    return drop_enumerator<T>(*this, count);
  }

  auto take(int count) && noexcept  {
    return take_enumerator<T>(*this, count);
  }

  auto until_eq(const T &element) && noexcept {
    return until([&](const T &x){ return element == x; });
  }

  auto where_neq(const T &element) && noexcept {
    return where([&](const T &x){ return element != x; });
  }

  template<typename U = T, typename F>
  auto select(F func) && {
    return select_enumerator<U, T, F>(*this, std::move(func));
  }

  template<typename F>
  auto until(F func) {
    return until_enumerator<T, F>(*this, std::move(func));
  }

  template<typename F>
  auto where(F func) {
    return where_enumerator<T, F>(*this, std::move(func));
  }

  std::vector<T> to_vector() {
    std::vector<T> res;

    copy_to(std::back_inserter(res));
    return res;
  }

  template<typename Iter>
  void copy_to(Iter it) {
    for (; *this; ++*this, ++it)
      *it = **this;
  }
};

template<typename T, typename Iter>
class range_enumerator final : public enumerator<T> {
public:
  explicit range_enumerator(Iter begin, Iter end) noexcept : begin_(begin), end_(end) {
  }

  T operator*() noexcept override
  {
    return *begin_;
  }

  void operator++() override
  {
    begin_++;
  }

  explicit operator bool() noexcept override
  {
    return begin_ != end_;
  }

private:
  Iter begin_, end_;
};

template<typename T>
class drop_enumerator final : public enumerator<T> {
public:
  explicit drop_enumerator(enumerator<T> &parent, int count) noexcept : parent_(parent) {
    for (int pos = 0; pos < count && parent_; ++pos)
      ++parent_;
  }

  void operator++() override
  {
    ++parent_;
  }

  T operator*() noexcept override
  {
    return *parent_;
  }

  explicit operator bool() noexcept override
  {
    return static_cast<bool>(parent_);
  }

private:
  enumerator<T> &parent_;
};

template<typename T>
class take_enumerator final : public enumerator<T> {
public:
  explicit take_enumerator(enumerator<T> &parent, int count) noexcept : parent_(parent), left_(count) {
  }

  void operator++() override
  {
    left_--;
    if (0 < left_)
      ++parent_;
  }

  T operator*() noexcept override
  {
    return *parent_;
  }

  explicit operator bool() noexcept override
  {
    return parent_ && 0 < left_;
  }

private:
  enumerator<T> &parent_;
  int left_;
};

template<typename T, typename F>
class until_enumerator final : public enumerator<T> {
public:
  explicit until_enumerator(enumerator<T> &parent, F predicate) : parent_(parent), predicate_(std::move(predicate)) {
    if (parent_)
      satisfied_ = !predicate_(*parent_);
  }

  void operator++() override
  {
    ++parent_;
    if (parent_)
      satisfied_ = !predicate_(*parent_);
  }

  T operator*() noexcept override
  {
    return *parent_;
  }

  explicit operator bool() noexcept override
  {
    return parent_ && satisfied_;
  }

private:
  enumerator<T> &parent_;
  F predicate_;
  bool satisfied_ = false;
};

template<typename T, typename U, typename F>
class select_enumerator final : public enumerator<T> {
public:
  explicit select_enumerator(enumerator<U> &parent, F func) : parent_(parent), func_(std::move(func)) {
    if (parent_)
      lastElement_ = func_(*parent_);
  }

  void operator++() override
  {
    ++parent_;
    if (parent_)
      lastElement_ = func_(*parent_);
  }

  T operator*() noexcept override
  {
    return lastElement_;
  }

  explicit operator bool() noexcept override
  {
    return static_cast<bool>(parent_);
  }

private:
  enumerator<U> &parent_;
  F func_;
  T lastElement_;
};

template<typename T, typename F>
class where_enumerator final : public enumerator<T> {
public:
  explicit where_enumerator(enumerator<T> &parent, F func) : parent_(parent), func_(std::move(func)) {
    while (parent_ && !func_(*parent_))
      ++parent_;
  }

  void operator++() override
  {
    ++parent_;
    while (parent_ && !func_(*parent_))
      ++parent_;
  }

  T operator*() noexcept override
  {
    return *parent_;
  }

  explicit operator bool() noexcept override
  {
    return static_cast<bool>(parent_);
  }

private:
  enumerator<T> &parent_;
  F func_;
};

} // namespace impl

template<typename T>
auto from(T begin, T end) noexcept {
  return impl::range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
}

} // namespace linq

#endif
