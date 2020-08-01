#ifndef _MY_VECTOR_IMPL_H
#define _MY_VECTOR_IMPL_H

#include <exception>
#include <cstdlib>
#include <cassert>
#include <cmath>

namespace my_vector
{
  template<typename T>
  size_t my_vector<T>::getMinPowerOfTwoCeil(size_t n)
  {
    assert(n > 0);
    assert(n < (size_t(1) << (sizeof(size_t) * 8 - 1)));
    size_t tmp = n, power = 0;
    int needIncr = 0;

    for (size_t i = 0; i < sizeof(size_t) * 8; ++i)
    {
      if (tmp & 1)
      {
        power = i;
        tmp >>= 1;
        if (tmp)
          needIncr = 1;
        else
          break;
      }
      else
        tmp >>= 1;
    }
    return 1 << (power + needIncr);
  }

  template<typename T>
  void my_vector<T>::vector_holder::swap(vector_holder &h1, vector_holder &h2) noexcept
  {
    std::swap(h1.capacity_, h2.capacity_);
    std::swap(h1.size_, h2.size_);
    std::swap(h1.array_, h2.array_);
  }

  template<typename T>
  my_vector<T>::vector_holder::vector_holder(size_t n) : capacity_{n}, size_{0}, array_{nullptr}
  {
    if (capacity_ > 0)
    {
      array_ = static_cast<T *>(std::aligned_alloc(alignof(T), sizeof(T) * capacity_));

      if (array_ == nullptr)
        throw std::bad_alloc();
    }
  }

  template<typename T>
  my_vector<T>::vector_holder::vector_holder(const vector_holder &other) : vector_holder{other.capacity_}
  {
    for (size_ = 0; size_ < other.size_; ++size_)
      new(array_ + size_) T{other.array_[size_]};
  }

  template<typename T>
  my_vector<T>::vector_holder::vector_holder(vector_holder &&other) noexcept :
    vector_holder{0}
  {
    swap(*this, other);
  }

  template<typename T>
  my_vector<T>::vector_holder::~vector_holder()
  {
    for (size_t i = 0; i < size_; ++i)
      array_[i].~T();
    free(array_);
  }

  template<typename T>
  auto my_vector<T>::vector_holder::operator=(vector_holder other) -> vector_holder &
  {
    swap(*this, other);

    return *this;
  }

  template<typename T>
  void my_vector<T>::vector_holder::copy_elements(const vector_holder &other, size_t count)
  {
    assert(this != &other);
    assert(count <= other.size_);
    assert(capacity_ >= count);

    for (; size_ > 0; --size_)
      array_[size_ - 1].~T();
    for (size_ = 0; size_ < count; ++size_)
      new(array_ + size_) T{other.array_[size_]};
  }

  template<typename T>
  my_vector<T>::my_vector() noexcept : holder_{0}
  {

  }

  template<typename T>
  my_vector<T>::my_vector(std::size_t n) : holder_{getMinPowerOfTwoCeil(n)}
  {
    for (; holder_.size_ < n; ++holder_.size_)
      new(holder_.array_ + holder_.size_) T();
  }

  template<typename T>
  my_vector<T>::my_vector(const my_vector &other) : holder_{other.holder_}
  {

  }

  template<typename T>
  my_vector<T>::my_vector(my_vector &&other) noexcept : holder_{0}
  {
    std::swap(holder_, other.holder_);
  }

  template<typename T>
  my_vector<T> & my_vector<T>::operator=(const my_vector &other)
  {
    if (this != &other)
      holder_ = other.holder_;

    return *this;
  }

  template<typename T>
  my_vector<T> & my_vector<T>::operator=(my_vector<T> &&other) noexcept
  {
    std::swap(holder_, other.holder_);

    return *this;
  }

  template<typename T>
  std::size_t my_vector<T>::size() const noexcept
  {
    return holder_.size_;
  }

  template<typename T>
  std::size_t my_vector<T>::capacity() const noexcept
  {
    return holder_.capacity_;
  }

  template<typename T>
  bool my_vector<T>::empty() const noexcept
  {
    return holder_.size_ == 0;
  }

  template<typename T>
  void my_vector<T>::resize(std::size_t n)
  {
    if (n < holder_.size_)
    {
      for (; holder_.size_ > n; --holder_.size_)
        holder_.array_[holder_.size_ - 1].~T();
    }
    else
    {
      size_t cpt = holder_.capacity_;
      if (n > holder_.capacity_)
        cpt = getMinPowerOfTwoCeil(n);

      if (cpt > holder_.capacity_)
      {
        vector_holder tmp(cpt);

        tmp.copy_elements(holder_, holder_.size_);
        for (; tmp.size_ < n; ++tmp.size_)
          new(tmp.array_ + tmp.size_) T{};

        holder_ = std::move(tmp);
      }
      else
      {
        size_t startSize = holder_.size_;
        try
        {
          for (; holder_.size_ < n; ++holder_.size_)
            new(holder_.array_ + holder_.size_) T{};
        }
        catch (const std::exception &e)
        {
          for (; holder_.size_ > startSize; --holder_.size_)
            holder_.array_[holder_.size_ - 1].~T();
          throw e;
        }
      }
    }
  }

  template<typename T>
  void my_vector<T>::reserve(std::size_t n)
  {
    if (n == 0)
      return;
    n = getMinPowerOfTwoCeil(n);
    if (n > holder_.capacity_)
    {
      vector_holder tmp(n);

      tmp.copy_elements(holder_, holder_.size_);

      holder_ = std::move(tmp);
    }
  }

  template<typename T>
  T & my_vector<T>::operator[](std::size_t index)
  {
    if (index >= holder_.size_)
      throw std::out_of_range("Bad index");
    return holder_.array_[index];
  }

  template<typename T>
  const T & my_vector<T>::operator[](std::size_t index) const
  {
    if (index >= holder_.size_)
      throw std::out_of_range("Bad index");
    return holder_.array_[index];
  }

  template<typename T>
  void my_vector<T>::push_back(T t)
  {
    reserve(holder_.size_ + 1);
    new(holder_.array_ + holder_.size_) T(std::move(t));
    holder_.size_++;
  }

  template<typename T>
  void my_vector<T>::pop_back()
  {
    if (holder_.size_ == 0)
      throw std::logic_error("Popping from empty vector");
    holder_.array_[--holder_.size_].~T();
  }

  template<typename T>
  void my_vector<T>::clear() noexcept
  {
    for (; holder_.size_ > 0; --holder_.size_)
      holder_.array_[holder_.size_ - 1].~T();
  }
}

template<typename T>
std::ostream & my_vector::operator<<(std::ostream &stream, const my_vector<T> &v)
{
  size_t i = 0;

  for (; i < v.size() - 1; ++i)
    stream << v[i] << ' ';
  if (v.size() > 0)
    stream << v[i];

  return stream;
}

#endif //_MY_VECTOR_IMPL_H
