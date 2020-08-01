#ifndef _BIN_MANIP_H
#define _BIN_MANIP_H

#include <stdint.h>
#include <ostream>
#include <istream>

void CheckStream(const std::basic_ios<char> &s);

class stream_checker final
{
public:
  std::basic_ostream<char> &operator<<(std::basic_ostream<char> &stream) const;
  std::basic_istream<char> &operator>>(std::basic_istream<char> &stream) const;
};

std::basic_ostream<char> &operator<<(std::basic_ostream<char> &stream, const stream_checker &checker);
std::basic_istream<char> &operator>>(std::basic_istream<char> &stream, const stream_checker &checker);

class write_le_int32 final
{
public:
  explicit write_le_int32(int32_t n);
  std::basic_ostream<char> &operator<<(std::basic_ostream<char> &stream) const;

private:
  int32_t num;
};

class read_le_int32 final
{
public:
  explicit read_le_int32(int32_t &n);
  std::basic_istream<char> &operator>>(std::basic_istream<char> &stream) const;

private:
  int32_t &ref;
};

std::basic_ostream<char> &operator<<(std::basic_ostream<char> &stream, const write_le_int32 &man);
std::basic_istream<char> &operator>>(std::basic_istream<char> &stream, const read_le_int32 &man);

class write_bool final
{
public:
  explicit write_bool(bool n);
  std::basic_ostream<char> &operator<<(std::basic_ostream<char> &stream) const;

private:
  bool num;
};

class read_bool final
{
public:
  explicit read_bool(bool &n);
  std::basic_istream<char> &operator>>(std::basic_istream<char> &stream) const;

private:
  bool &ref;
};

std::basic_ostream<char> &operator<<(std::basic_ostream<char> &stream, const write_bool &man);
std::basic_istream<char> &operator>>(std::basic_istream<char> &stream, const read_bool &man);

class write_c_str final
{
public:
  explicit write_c_str(char *s);
  std::basic_ostream<char> &operator<<(std::basic_ostream<char> &stream) const;

private:
  char *str;
};

class read_c_str final
{
public:
  explicit read_c_str(char *n, size_t ms);
  std::basic_istream<char> &operator>>(std::basic_istream<char> &stream) const;

private:
  char *ref;
  size_t max_size;
};

std::basic_ostream<char> &operator<<(std::basic_ostream<char> &stream, const write_c_str &man);
std::basic_istream<char> &operator>>(std::basic_istream<char> &stream, const read_c_str &man);

#endif //_BIN_MANIP_H
