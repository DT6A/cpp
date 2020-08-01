#ifndef __MATRIX_H
#define __MATRIX_H

#include <exception>
#include <string>
#include <cstddef>

class MatrixException final : public std::exception
{
public:
  enum ExceptionType
  {
    ADD, MUL, ACCESS, INVALID_SIZE, FOPEN, READING
  };

  explicit MatrixException(ExceptionType type) noexcept;

  const char * what() const noexcept override;

private:
  ExceptionType _type;
};

class Matrix final
{
public:
  explicit Matrix(int32_t rows = 0, int32_t cols = 0);
  Matrix(const std::string &fileName);
  Matrix(const Matrix &other);
  ~Matrix();

  void print() const;
  int getElement(int32_t row, int32_t col) const;

  Matrix & operator=(Matrix other);
  Matrix & operator+=(const Matrix &other);
  Matrix & operator*=(const Matrix &other);

private:
  int32_t _rows, _cols; // Not size_t to process negative numbers and avoid big allocations
  int32_t **_data;

  static int ** MatrixAllocator(int32_t rows, int32_t cols);
};


#endif //__MATRIX_H
