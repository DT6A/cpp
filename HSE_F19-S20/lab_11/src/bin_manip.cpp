#include <string>
#include <cassert>
#include <cstring>
#include <iostream>

#include "bin_manip.h"

std::basic_ostream<char> &stream_checker::operator<<(std::basic_ostream<char> &stream) const
{
  if (stream.bad())
  {
    std::cerr << "A problem occurred while writing file. Probably you ran out of space\n";
    std::abort();
  }
  if (stream.fail())
  {
    std::cerr << "Failed to write\n";
    std::abort();
  }
  return stream;
}

std::basic_istream<char> &stream_checker::operator>>(std::basic_istream<char> &stream) const
{
  if (stream.bad())
  {
    std::cerr << "A problem occurred while reading file. Probably you ran out of space\n";
    std::abort();
  }
  if (stream.fail())
  {
    std::cerr << "Failed to read\n";
    std::abort();
  }
  return stream;
}

std::basic_ostream<char> &operator<<(std::basic_ostream<char> &stream, const stream_checker &checker)
{
  return checker << stream;
}

std::basic_istream<char> &operator>>(std::basic_istream<char> &stream, const stream_checker &checker)
{
  return checker >> stream;
}

write_le_int32::write_le_int32(int32_t n) : num{n}
{

}


read_le_int32::read_le_int32(int32_t &n) : ref{n}
{

}

std::basic_ostream<char> &write_le_int32::operator<<(std::basic_ostream<char> &stream) const
{
  for (int i = 0; i < 4; ++i)
  {
    char byte = (num >> i * 8) & 255;
    stream.write(&byte, 1);
  }
  return stream;
}

std::basic_istream<char> &read_le_int32::operator>>(std::basic_istream<char> &stream) const
{
  ref = 0;
  for (int i = 0; i < 4; ++i)
  {
    char byte = 0;
    stream.read(&byte, 1);
    ref |= int32_t((unsigned char)(byte)) << i * 8;
  }
  return stream;
}

std::basic_ostream<char> &operator<<(std::basic_ostream<char> &stream, const write_le_int32 &man)
{
  man << stream;
  return stream;
}

std::basic_istream<char> &operator>>(std::basic_istream<char> &stream, const read_le_int32 &man)
{
  man >> stream;
  return stream;
}

write_bool::write_bool(bool b) : num{b}
{

}


read_bool::read_bool(bool &n) : ref{n}
{

}

std::basic_ostream<char> &write_bool::operator<<(std::basic_ostream<char> &stream) const
{
  char byte = num & 255;
  stream.write(&byte, 1);
  return stream;
}

std::basic_istream<char> &read_bool::operator>>(std::basic_istream<char> &stream) const
{
  ref = 0;
  stream.read((char *)&ref, 1);
  return stream;
}

std::basic_ostream<char> &operator<<(std::basic_ostream<char> &stream, const write_bool &man)
{
  man << stream;
  return stream;
}

std::basic_istream<char> &operator>>(std::basic_istream<char> &stream, const read_bool &man)
{
  man >> stream;
  return stream;
}

write_c_str::write_c_str(char *s) : str{s}
{
  assert(s != nullptr);
}


read_c_str::read_c_str(char *s, size_t ms) : ref{s}, max_size{ms}
{
  assert(s != nullptr);
}

std::basic_ostream<char> &write_c_str::operator<<(std::basic_ostream<char> &stream) const
{
  stream.write(str, strlen(str) + 1);
  return stream;
}

std::basic_istream<char> &read_c_str::operator>>(std::basic_istream<char> &stream) const
{
  stream.getline(ref, max_size, 0);
  return stream;
}

std::basic_ostream<char> &operator<<(std::basic_ostream<char> &stream, const write_c_str &man)
{
  man << stream;
  return stream;
}

std::basic_istream<char> &operator>>(std::basic_istream<char> &stream, const read_c_str &man)
{
  man >> stream;
  return stream;
}
