#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>
#include <iostream>

namespace my_vector
{
  template<typename T>
  class my_vector final
  {
  public:
    my_vector() noexcept;
    explicit my_vector(std::size_t n);
    my_vector(const my_vector &other);
    my_vector(my_vector &&other) noexcept;
    my_vector & operator=(const my_vector &other);
    my_vector & operator=(my_vector &&other) noexcept;
    ~my_vector() = default;

    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;
    bool empty() const noexcept;

    void resize(std::size_t n);
    void reserve(std::size_t n);

    T & operator[](std::size_t index);
    const T & operator[](std::size_t index) const;

    void push_back(T t);
    void pop_back();
    void clear() noexcept;

  private:
    class vector_holder final
    {
    public:
      explicit vector_holder(size_t n);
      vector_holder(const vector_holder &other);
      vector_holder(vector_holder &&other) noexcept;
      ~vector_holder();

      auto operator=(vector_holder other) -> vector_holder &;

      void copy_elements(const vector_holder &other, size_t count);

      static void swap(vector_holder &h1, vector_holder &h2) noexcept;

      size_t capacity_;
      size_t size_;
      T *array_;
    } holder_;

    static size_t getMinPowerOfTwoCeil(size_t n);
  };

  template<typename T>
  std::ostream & operator<<(std::ostream &stream, const my_vector<T> &v);
}

#include "my_vector_impl.h"

#endif  // MY_VECTOR_H_