#include <cstring>
#include <string>
#include <cstdlib>

#include "bin_manip.h"
#include "employees.h"

Employee::Employee(const Employee &e) : _base_salary{e._base_salary}
{
  _name = new char[strlen(e._name) + 1];
  strcpy(_name, e._name);
}

Employee::~Employee()
{
  delete[] _name;
}

std::ostream& Employee::writeBase(std::ostream& stream) const
{
  stream << "Name: " << stream_checker() << _name << stream_checker() <<
    "\nBase Salary: " << stream_checker() << _base_salary << stream_checker() << '\n' <<
    stream_checker();
  return stream;
}

std::istream& Employee::readBase(std::istream& stream)
{
  std::string name;

  stream >> name >> stream_checker() >> _base_salary >> stream_checker();

  _name = new char[name.size() + 1];
  strcpy(_name, name.c_str());
  return stream;
}

std::ofstream& Employee::writeBase(std::ofstream& stream) const
{
  stream << write_c_str(_name) << stream_checker() << write_le_int32(_base_salary) << stream_checker();
  return stream;
}

std::ifstream& Employee::readBase(std::ifstream& stream)
{
  _name = new char[max_name_len];
  stream >> read_c_str(_name, max_name_len) >> stream_checker();
  stream >> read_le_int32(_base_salary) >> stream_checker();
  return stream;
}

Developer::Developer(const Developer &d) :
  Employee{d}, _has_bonus{d._has_bonus}
{

}

int Developer::salary() const
{
  int salary = _base_salary;

  if (_has_bonus)
    salary += 1000;

  return salary;
}

std::ostream& Developer::operator<<(std::ostream& stream) const
{
  stream << "Developer\n" << stream_checker();
  writeBase(stream);
  stream << "Has bonus: " << stream_checker() << (_has_bonus ? "+\n" : "-\n") << stream_checker();

  return stream;
}

std::istream& Developer::operator>>(std::istream& stream)
{
  readBase(stream);
  stream >> _has_bonus >> stream_checker();

  return stream;
}

std::ofstream& Developer::operator<<(std::ofstream& stream) const
{
  stream << write_le_int32(E_DEV) << stream_checker();
  writeBase(stream);
  stream << write_bool(_has_bonus) << stream_checker();

  return stream;
}

std::ifstream& Developer::operator>>(std::ifstream& stream)
{
  readBase(stream);
  stream >> read_bool(_has_bonus) >> stream_checker();

  return stream;
}

SalesManager::SalesManager(const SalesManager &m) :
  Employee{m}, _sold_nm{m._sold_nm}, _price{m._price}
{

}

int SalesManager::salary() const
{
  return _base_salary + _sold_nm * _price * 0.01;
}

std::ostream& SalesManager::operator<<(std::ostream& stream) const
{
  stream << "Sales Manager\n" << stream_checker();
  writeBase(stream);
  stream << "Sold items: " << stream_checker() << _sold_nm << stream_checker()
    << "\nItem price: " << stream_checker() << _price << stream_checker() << '\n' << stream_checker();

  return stream;
}

std::istream& SalesManager::operator>>(std::istream& stream)
{
  readBase(stream);
  stream >> _sold_nm >> stream_checker() >> _price >> stream_checker();

  return stream;
}

std::ofstream& SalesManager::operator<<(std::ofstream& stream) const
{
  stream << write_le_int32(E_SM) << stream_checker();
  writeBase(stream);
  stream << write_le_int32(_sold_nm) << stream_checker() << write_le_int32(_price) << stream_checker();

  return stream;
}

std::ifstream& SalesManager::operator>>(std::ifstream& stream)
{
  readBase(stream);
  stream >> read_le_int32(_sold_nm) >> stream_checker() >> read_le_int32(_price) >> stream_checker();

  return stream;
}

std::ostream& operator<<(std::ostream& s, const Employee& e)
{
  e << s;
  return s;
}

std::istream& operator>>(std::istream& s, Employee& e)
{
  e >> s;
  return s;
}

std::ofstream& operator<<(std::ofstream& s, const Employee& e)
{
  e << s;
  return s;
}

std::ifstream& operator>>(std::ifstream& s, Employee& e)
{
  e >> s;
  return s;
}

EmployeesArray::EmployeesArray(int32_t capacity) : _capacity{capacity}, _size{0}
{
  _employees = new Employee*[_capacity];
}

EmployeesArray::~EmployeesArray()
{
  for (int i = 0; i < _size; ++i)
    delete _employees[i];

  delete[] _employees;
}

void EmployeesArray::add(Employee *e)
{
  if (_size == _capacity)
  {
    _capacity *= 2;
    Employee **tmp = new Employee*[_capacity];
    memcpy(tmp, _employees, sizeof(Employee *) * _size);
    delete[] _employees;
    _employees = tmp;
  }

  _employees[_size++] = e;
}

int EmployeesArray::total_salary() const
{
  int S = 0;

  for (int i = 0; i < _size; ++i)
    S += _employees[i]->salary();

  return S;
}

std::ostream& EmployeesArray::operator<<(std::ostream& stream) const
{
  for (int i = 0; i < _size; ++i)
    stream << i + 1 << stream_checker() << ". " << stream_checker() << *_employees[i] << stream_checker();
  stream << "== Total salary: " << stream_checker() << total_salary() << stream_checker()
    << '\n' << stream_checker();
  stream << '\n' << stream_checker();

  return stream;
}

std::istream& EmployeesArray::operator>>(std::istream& stream)
{
  int32_t type = 0;
  Employee *e = nullptr;

  stream >> type >> stream_checker();

  if (type == E_DEV)
    e = new Developer();
  else if (type == E_SM)
    e = new SalesManager();
  else
    stream.setstate(std::ios::failbit);

  stream >> stream_checker() >> *e >> stream_checker();
  add(e);

  return stream;
}


std::ofstream& EmployeesArray::operator<<(std::ofstream& stream) const
{
  stream << write_le_int32(_size) << stream_checker();
  for (int i = 0; i < _size; ++i)
    stream << *_employees[i];

  return stream;
}

std::ifstream& EmployeesArray::operator>>(std::ifstream& stream)
{
  int32_t notes = 0;
  stream >> read_le_int32(notes) >> stream_checker();

  for (int i = 0; i < notes; ++i)
  {
    int32_t type = 0;
    Employee *e = nullptr;

    stream >> read_le_int32(type) >> stream_checker();

    if (type == E_DEV)
      e = new Developer();
    else if (type == E_SM)
      e = new SalesManager();
    else
    {
      stream.setstate(std::ios::failbit);
      break;
    }

    stream  >> *e >> stream_checker();
    add(e);
  }

  return stream;
}

std::ostream& operator<<(std::ostream& s, const EmployeesArray& e)
{
  e << s;
  return s;
}

std::istream& operator>>(std::istream& s, EmployeesArray& e)
{
  e >> s;
  return s;
}

std::ofstream& operator<<(std::ofstream& s, const EmployeesArray& e)
{
  e << s;
  return s;
}

std::ifstream& operator>>(std::ifstream& s, EmployeesArray& e)
{
  e >> s;
  return s;
}