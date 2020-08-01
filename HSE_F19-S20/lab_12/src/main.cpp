#include <iostream>
#include <cstring>
#include <cassert>

#include "my_vector.h"

namespace product
{
  class Product final
  {
  public:
    Product(const char* name, int quantity, double price) : quantity_{quantity}, price_{price}
    {
      name_ = new char[strlen(name) + 1];
      strcpy(name_, name);
    }

    Product(const Product &other) : quantity_{other.quantity_}, price_{other.price_}
    {
      name_ = new char[strlen(other.name_) + 1];
      strcpy(name_, other.name_);
    }

    Product(Product &&other) : name_{other.name_}, quantity_{other.quantity_}, price_{other.price_}
    {
      other.name_ = nullptr;
    }

    ~Product()
    {
      delete[] name_;
    }

    Product & operator=(Product other)
    {
      std::swap(name_, other.name_);
      std::swap(quantity_, other.quantity_);
      std::swap(price_, other.price_);
      return *this;
    }

    std::ostream & operator<<(std::ostream &stream) const
    {
      stream << name_ << ' ' << quantity_ << ' ' << price_;
      return stream;
    }

  private:
    char *name_;  // Указатель владеет C-style строкой, на которую указывает.
    int quantity_;
    double price_;
  };

  std::ostream & operator<<(std::ostream &stream, const Product &p)
  {
    return p << stream;
  }

  void print(const my_vector::my_vector<Product>& v)
  {
    try
    {
      std::cout << v << std::endl;
    }
    catch (const std::logic_error &e)
    {
      std::cout.clear(std::ostream::failbit);
      if (std::cout.bad())
        throw e;
      std::cout << e.what();
    }
  }
}  // namespace product

namespace tests
{
  template<typename T>
  void test_my_vector(T obj1, T obj2)
  {
    my_vector::my_vector<T> v;
    assert(v.size() == 0);
    assert(v.empty());
    try
    {
      v.pop_back();
      assert(false);
    }
    catch(...) {}

    v.push_back(obj1);
    assert(v.size() == 1);
    assert(!v.empty());
    v[0];
    v[0] = obj1;
    v.push_back(obj2);
    assert(v.size() == 2);
    assert(v.capacity() == 2);
    v[0] = v[1];
    v.push_back(obj2);
    assert(v.capacity() == 4);
    v.reserve(13);
    assert(v.capacity() == 16);
    v.pop_back();
    assert(v.size() == 2);
    try
    {
      v[-1];
      assert(false);
    }
    catch(...) {}
    try
    {
      v[3];
      assert(false);
    }
    catch(...) {}
    my_vector::my_vector<T> v2(v);
    assert(v2.size() == 2);
    assert(v2.capacity() == 16);
    v.clear();
    assert(v.size() == 0);
    assert(v.capacity() == 16);
    v = v2;
    assert(v.size() == 2);
    assert(v.capacity() == 16);
    v2.push_back(obj1);

    my_vector::my_vector<T> vRVM(std::move(v));
    assert(vRVM.size() == 2);
    assert(vRVM.capacity() == 16);
    vRVM = std::move(v2);
    assert(vRVM.size() == 3);
    assert(vRVM.capacity() == 16);
    vRVM[0] = vRVM[1];
    vRVM[0] = vRVM[1] = std::move(vRVM[2]);
  }

  template<typename T>
  void test_my_vector_default_constructible(T obj1, T obj2)
  {
    test_my_vector(obj1, obj2);
    my_vector::my_vector<T> v(3);
    assert(v.size() == 3);
    assert(v.capacity() == 4);
    v.resize(10);
    assert(v.size() == 10);
    assert(v.capacity() == 16);
    v.resize(5);
    assert(v.size() == 5);
    assert(v.capacity() == 16);
  }
} // namespace tests

int main()
{
  std::cout.exceptions(std::ios::failbit | std::ios::badbit);
  try
  {
    tests::test_my_vector<product::Product>(product::Product("asdf", 4, 12.0),
                                            product::Product("qwe", -1, 7.5));
    tests::test_my_vector_default_constructible<int>(5, 10);
    std::cout << "Tests: OK\n";
  }
  catch (const std::exception &e)
  {
    std::cout << "Tests: Failed\n";
    std::cout << e.what();
  }

  my_vector::my_vector<product::Product> v;
  v.push_back(product::Product("asdf", 4, 12.0));
  v.push_back(product::Product("qwe", -1, 7.5));

  product::print(v);
  return 0;
}