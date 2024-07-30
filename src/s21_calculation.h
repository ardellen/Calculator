#ifndef S21_CALCULATION_H
#define S21_CALCULATION_H

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
class Calculator {
 public:
  /**
   * @brief Выполняет вычисления арифметического выражения.
   *
   * @param tokens Список токенов, представляющих арифметическое выражение.
   * @return Результат вычислений.
   */
  double Calculation(const std::queue<Token>& tokens);

  /**
   * @brief Сбрасывает состояние калькулятора.
   *
   * Этот метод очищает стеки и другие данные, восстанавливая исходное
   * состояние.
   */
  void Reset();

 private:
  /**
   * @brief Извлекает значение из результата вычислений.
   *
   * @return Извлеченное значение.
   */
  double PopFromResult();

  /**
   * @brief Добавляет значение в результат вычислений.
   *
   * @param number Значение для добавления.
   */
  void PushToResult(double number);

  std::queue<Token>
      polish_stack_; /**< Стек для хранения токенов в постфиксной нотации. */
  std::stack<double>
      result_; /**< Стек для хранения промежуточных результатов вычислений. */
};

}  // namespace s21

#endif  // S21_CALCULATION_H
