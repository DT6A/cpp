#ifndef _TEST_H
#define _TEST_H

#include <cstddef>

#define DO_CHECK(EXPR) Test::check((EXPR), __PRETTY_FUNCTION__, __FILE__, __LINE__);

class Test
{
public:
  static int failedNum; // количество тестов, которые сломались
  static int totalNum;  // общее количество тестов

  /** Проверяет условие на верность (expr).
      Сообщает об результате пользователю, в случае неудачи подробно сообщает об источнике. */
  static void check(bool expr, const char *func, const char  *filename, std::size_t lineNum);

  static void showFinalResult();

  /** Запускает все тесты в конкретном наборе тестов */
  virtual void runAllTests() = 0;

  // Можно добавлять методы при необходимости
};


#endif //_TEST_H
