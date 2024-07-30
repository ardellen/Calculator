#ifndef S21_POLISH_NOTATION_H
#define S21_POLISH_NOTATION_H

#include <list>
#include <queue>
#include <stack>

#include "s21_token.h"

namespace s21 {
/**
 * @brief Класс Calculator выполняет вычисления арифметического выражения.
 *
 * Этот класс отвечает за выполнение вычислений, представленных в виде списка
 * токенов.
 */
class Converter {
 public:
  /**
   * @brief Конструктор класса Calculator.
   */
  Converter() = default;

  /**
   * @brief Деструктор класса Calculator.
   */
  ~Converter() = default;

  /**
   * @brief Возвращает очередь токенов в польской нотации.
   *
   * @return Очередь токенов в польской нотации.
   */
  std::queue<Token> GetPolishNotation() { return polish_stack_; };

  /**
   * @brief Выполняет вычисления арифметического выражения.
   *
   * @param tokens Список токенов, представляющих арифметическое выражение.
   * @return Результат вычислений.
   */
  void ConvertPolishNotation(const std::list<Token>& tokens, double x_value);

  /**
   * @brief Сбрасывает состояние конвертера в польскую нотацию.
   *
   * Этот метод восстанавливая исходное состояние конвертера.
   */
  void Reset();

 private:
  std::queue<Token>
      polish_stack_; /**< Стек для хранения токенов в постфиксной нотации. */
};

}  // namespace s21

#endif  // S21_POLISH_NOTATION_H
