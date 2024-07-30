#include "s21_calculation.h"

namespace s21 {

/**
 * @brief Добавляет значение в результат вычислений.
 *
 * @param number Значение для добавления.
 */
void Calculator::PushToResult(double number) { result_.push(number); }

/**
 * @brief Извлекает значение из результата вычислений.
 *
 * @return Извлеченное значение.
 */
double Calculator::PopFromResult() {
  double return_number = result_.top();
  result_.pop();
  return return_number;
}

/**
 * @brief Сбрасывает состояние калькулятора.
 *
 * Этот метод очищает стеки и другие данные, восстанавливая исходное
 * состояние.
 */
void Calculator::Reset() {
  polish_stack_ = std::queue<Token>();
  while (!result_.empty()) {
    result_.pop();
  }
}

/**
 * @brief Выполняет вычисления арифметического выражения.
 *
 * @param tokens Список токенов, представляющих арифметическое выражение.
 * @return Результат вычислений.
 */
double Calculator::Calculation(const std::queue<Token>& tokens) {
  polish_stack_ = tokens;
  while (!polish_stack_.empty()) {
    Token top_token = polish_stack_.front();
    polish_stack_.pop();
    // std::cout << top_token.GetName();  // TODO: не забудь убрать
    std::visit(overloaded{[&](double value) { PushToResult(value); },
                          [&](const unary_function& func) {
                            if (result_.empty()) {
                              throw std::runtime_error(
                                  "Stack underflow for unary operation");
                            }
                            double arg = PopFromResult();
                            PushToResult(func(arg));
                          },
                          [&](const binary_function& func) {
                            if (result_.size() < 2) {
                              throw std::runtime_error(
                                  "Stack underflow for binary operation");
                            }
                            double right = PopFromResult();
                            double left = PopFromResult();
                            PushToResult(func(left, right));
                          },
                          [&](auto&) {}},
               top_token.GetFunction());
  }
  return PopFromResult();
}
}  // namespace s21
