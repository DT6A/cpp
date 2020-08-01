#ifndef _EMPLOYEES_H
#define _EMPLOYEES_H

#include <iostream>
#include <fstream>
#include <stdint.h>

#include "bin_manip.h"

constexpr int const max_name_len = 100;

enum Employee_type
{
  E_DEV = 1, E_SM = 2
};

class Employee
{
public:
  Employee() = default;
  Employee(const Employee &e);
  Employee& operator=(const Employee &e) = delete;

  virtual ~Employee();

  virtual std::ostream& operator<<(std::ostream& stream) const = 0;
  virtual std::istream& operator>>(std::istream& stream) = 0;
  virtual std::ofstream& operator<<(std::ofstream& stream) const = 0;
  virtual std::ifstream& operator>>(std::ifstream& stream) = 0;

  virtual int salary() const = 0;

protected:
  char *_name = nullptr;
  int32_t _base_salary;

  std::ostream& writeBase(std::ostream& stream) const;
  std::istream& readBase(std::istream& stream);
  std::ofstream& writeBase(std::ofstream& stream) const;
  std::ifstream& readBase(std::ifstream& stream);
};

class Developer final : public Employee
{
public:
  Developer() = default;
  Developer(const Developer &d);

  int salary() const override;

  std::ostream& operator<<(std::ostream& stream) const override;
  std::istream& operator>>(std::istream& stream) override;
  std::ofstream& operator<<(std::ofstream& stream) const override;
  std::ifstream& operator>>(std::ifstream& stream) override;

private:
  bool _has_bonus;
};

class SalesManager final : public Employee
{
public:
  SalesManager() = default;
  SalesManager(const SalesManager &m);

  int salary() const override;

  std::ostream& operator<<(std::ostream& stream) const override;
  std::istream& operator>>(std::istream& stream) override;
  std::ofstream& operator<<(std::ofstream& stream) const override;
  std::ifstream& operator>>(std::ifstream& stream) override;

private:
  int32_t _sold_nm, _price;
};

class EmployeesArray final
{
public:
  EmployeesArray(int32_t capacity = 3);
  ~EmployeesArray();

  void add(Employee *e);
  int total_salary() const;

  std::ostream& operator<<(std::ostream& stream) const;
  std::istream& operator>>(std::istream& stream);
  std::ofstream& operator<<(std::ofstream& stream) const;
  std::ifstream& operator>>(std::ifstream& stream);

private:
  Employee **_employees;
  int32_t _capacity, _size;
};

std::ostream& operator<<(std::ostream& s, const Employee& e);
std::istream& operator>>(std::istream& s, Employee& e);
std::ofstream& operator<<(std::ofstream& s, const Employee& e);
std::ifstream& operator>>(std::ifstream& s, Employee& e);

std::ostream& operator<<(std::ostream& s, const EmployeesArray& e);
std::istream& operator>>(std::istream& s, EmployeesArray& e);
std::ofstream& operator<<(std::ofstream& s, const EmployeesArray& e);
std::ifstream& operator>>(std::ifstream& s, EmployeesArray& e);

#endif //_EMPLOYEES_H
