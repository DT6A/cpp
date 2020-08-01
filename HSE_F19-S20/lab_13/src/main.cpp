#include <iostream>
#include <cstddef>

#include "my_array.h"

using lab_13::my_array;

template<typename T, std::size_t N>
void test_core() {
  my_array<T, N> a;
  const my_array<T, N> &ca = a;
  a.empty();
  ca.empty();
  a.size();
  ca.size();

  a.at(0);
  ca.at(0);
  a[0];
  ca[0];
  (void)static_cast<const T &>(a[0]);
  (void)static_cast<const T &>(ca[0]);
}

template<typename T, std::size_t N>
void test_assign() {
  my_array<T, N> a;
  const my_array<T, N> &ca = a;
  a.fill(T());

  a[0] = T();
  a[0] = a[0];
  a[0] = ca[0];
}

class NonCopyable {
public:
  NonCopyable() {}
private:
  NonCopyable(const NonCopyable&);
  NonCopyable& operator=(const NonCopyable);
};

namespace my_tests
{
  template<typename T, size_t N>
  void testDefaultCopyable(const T fillValue)
  {
    my_array<T, N> A;

    assert(sizeof(A) == N * sizeof(T));
    assert(A.size() == N);

    if (N > 0)
    {
      assert(!A.empty());
      A[0] = A[N - 1] = A[0];

      try
      {
        A.at(-1);
        assert(false);
      }
      catch (const std::out_of_range &e)
      {

      }

      try
      {
        A.at(N);
        assert(false);
      }
      catch (const std::out_of_range &e)
      {

      }

      A.fill(fillValue);

      for (size_t i = 0; i < N; ++i)
        assert(A[i] == fillValue);
    }
    else
    {
      assert(A.empty());
      try
      {
        A.at(0);
        assert(false);
      }
      catch (const std::out_of_range &e)
      {

      }
    }
  }

  template<size_t N>
  void testBool()
  {
    my_array<bool, N> A;

    assert(sizeof(A) <= N / 8 + 1 && sizeof(A) >= N / 8);
    assert(A.size() == N);

    if (N > 0)
    {
      assert(!A.empty());

      A[N - 1] = true;
      assert(A[N - 1] == true);
      A[0] = true;
      assert(A[0] == true);
      A[N - 1] = false;
      assert(A[N - 1] == false);
      A[0] = false;
      assert(A[0] == false);

      A[0] = A[N - 1] = true;
      assert(A[0] == true);
      A[N - 1] = A[0] = A[N - 1];
      assert(A[N - 1] && A[0]);

      for (size_t i = 0, val = true; i < N; ++i, val = !val)
        A[i] = val;
      for (size_t i = 0, val = true; i < N - 2; ++i, val = !val)
      {
        A[i] = A[i + 1] = A[i + 2];
        assert(bool(A[i]) == val);
        assert(bool(A[i + 1]) == val);
        assert(bool(A[i + 2]) == val);
      }

      try
      {
        A.at(-1);
        assert(false);
      }
      catch (const std::out_of_range &e)
      {

      }

      try
      {
        A.at(N);
        assert(false);
      }
      catch (const std::out_of_range &e)
      {

      }

      A.fill(true);
      for (size_t i = 0; i < N; ++i)
        assert(A[i]);

      A.fill(false);
      for (size_t i = 0; i < N; ++i)
        assert(!A[i]);

      A[0] = std::move(A[N - 1]);
    }
    else
    {
      assert(A.empty());
      try
      {
        A.at(0);
        assert(false);
      }
      catch (const std::out_of_range &e)
      {

      }
    }
  }
}

int main() {
  test_core<int, 10>();
  test_core<bool, 10>();
  test_core<NonCopyable, 10>();

  test_assign<int, 10>();
  test_assign<bool, 10>();

  my_tests::testDefaultCopyable<int, 10>(30);
  my_tests::testDefaultCopyable<float, 10>(239.30);
  my_tests::testDefaultCopyable<double, 0>(0);

  my_tests::testBool<0>();
  my_tests::testBool<8>();
  my_tests::testBool<10>();
}

