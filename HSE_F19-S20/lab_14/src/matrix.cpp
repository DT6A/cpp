#include <iostream>
#include <fstream>

#include "matrix.h"

MatrixException::MatrixException(ExceptionType type) noexcept : _type{type}
{

}

const char * MatrixException::what() const noexcept
{
  switch (_type)
  {
    case ExceptionType::MUL:
      return "MUL: #arg1.columns != #arg2.rows.";
    case ExceptionType::ADD:
      return "ADD: dimensions do not match.";
    case ExceptionType::ACCESS:
      return "ACCESS: bad index.";
    case ExceptionType::INVALID_SIZE:
      return "CREATE: invalid dimensions.";
    case ExceptionType::FOPEN:
      return "LOAD: unable to open file.";
    case ExceptionType::READING:
      return "LOAD: invalid file format.";
    default:
      return "Unknown error";
  }
}

int32_t ** Matrix::MatrixAllocator(int32_t rows, int32_t cols)
{
  if (rows > 0 && cols > 0)
  {
    int32_t *tmp = new int32_t[rows * cols];
    int32_t **data;

    try
    {
      data = new int32_t*[rows];
    }
    catch (const std::bad_alloc &e)
    {
      delete [] tmp;
      throw e;
    }

    for (int32_t i = 0; i < rows; ++i)
      data[i] = tmp + i * cols;

    return data;
  }
  else if (rows == 0 && cols == 0)
    return nullptr;
  else
    throw MatrixException(MatrixException::ExceptionType::INVALID_SIZE);
}

Matrix::Matrix(int32_t rows, int32_t cols) : _rows{rows}, _cols{cols}, _data{nullptr}
{
  _data = MatrixAllocator(_rows, _cols);
}

Matrix::Matrix(const std::string &fileName)
{
  std::ifstream file(fileName);

  if (!file.is_open())
    throw MatrixException(MatrixException::ExceptionType::FOPEN);

  file >> _rows >> _cols;

  if (file.fail() || file.bad())
    throw MatrixException(MatrixException::ExceptionType::READING);

  _data = MatrixAllocator(_rows, _cols);

  for (int32_t i = 0; i < _rows; ++i)
    for (int32_t j = 0; j < _cols; ++j)
    {
      file >> _data[i][j];
      if (file.fail() || file.bad())
      {
        delete [] _data[0];
        delete [] _data;
        throw MatrixException(MatrixException::ExceptionType::READING);
      }
    }
}

Matrix::Matrix(const Matrix &other) : _rows{other._rows}, _cols{other._cols}
{
  _data = MatrixAllocator(_rows, _cols);

  for (int32_t i = 0; i < _rows; ++i)
    for (int32_t j = 0; j < _cols; ++j)
      _data[i][j] = other._data[i][j];
}

Matrix::~Matrix()
{
  if (_data == nullptr)
    return;

  delete [] _data[0];
  delete [] _data;
}

void Matrix::print() const
{
  for (int32_t i = 0; i < _rows; ++i)
  {
    for (int32_t j = 0; j < _cols; ++j)
      std::cout << _data[i][j] << ' ';
    std::cout << '\n';
  }
}

int32_t Matrix::getElement(int32_t row, int32_t col) const
{
  if (row < 0 || row >= _rows || col < 0 || col >= _cols)
    throw MatrixException(MatrixException::ExceptionType::ACCESS);
  return _data[row][col];
}

Matrix & Matrix::operator=(Matrix other)
{
  std::swap(_data, other._data);
  std::swap(_rows, other._rows);
  std::swap(_cols, other._cols);

  return *this;
}

Matrix & Matrix::operator+=(const Matrix &other)
{
  if (_rows != other._rows || _cols != other._cols)
    throw MatrixException(MatrixException::ExceptionType::ADD);

  for (int32_t i = 0; i < _rows; ++i)
    for (int32_t j = 0; j < _cols; ++j)
      _data[i][j] += other._data[i][j];

  return *this;
}

Matrix & Matrix::operator*=(const Matrix &other)
{
  if (_cols != other._rows)
    throw MatrixException(MatrixException::ExceptionType::MUL);

  Matrix tmp(_rows, other._cols);

  for (int32_t i = 0; i < _rows; ++i)
    for (int32_t j = 0; j < other._cols; ++j)
    {
      int32_t elem = 0;

      for (int32_t k = 0; k < _cols; ++k)
        elem += _data[i][k] * other._data[k][j];
      tmp._data[i][j] = elem;
    }

  *this = tmp;

  return *this;
}
