#include "s21_polish_notation.h"

namespace s21 {

/**
 * @brief Сбрасывает состояние конвертера в польскую нотацию.
 *
 * Этот метод восстанавливая исходное состояние конвертера.
 */
void Converter::Reset() { polish_stack_ = std::queue<Token>(); }

/**
 * @brief Преобразует входной список токенов в постфиксную нотацию.
 *
 * @param tokens Список токенов, представляющих арифметическое выражение.
 */
void Converter::ConvertPolishNotation(const std::list<Token>& tokens,
                                      double x_value) {
  std::stack<Token> operator_stack;

  for (const Token& current_token : tokens) {
    if (current_token.GetType() == kNumber) {
      if (current_token.GetName() == "x") {
        Token token_x("x", kDefault, kNone, kNumber, x_value);
        polish_stack_.push(token_x);
      } else {
        polish_stack_.push(current_token);
      }
    } else if (current_token.GetName() == "(") {
      operator_stack.push(current_token);
    } else if (current_token.GetName() == ")") {
      while (!operator_stack.empty() && operator_stack.top().GetName() != "(") {
        polish_stack_.push(operator_stack.top());
        operator_stack.pop();
      }
      operator_stack.pop();
    } else {
      while (
          !operator_stack.empty() &&
          !(operator_stack.top().GetPriority() == 4 &&
            current_token.GetPriority() == 3) &&
          (operator_stack.top().GetPriority() > current_token.GetPriority() ||
           (operator_stack.top().GetPriority() == current_token.GetPriority() &&
            current_token.GetAssociativity() == kLeft))) {
        polish_stack_.push(operator_stack.top());
        operator_stack.pop();
      }
      operator_stack.push(current_token);
    }
  }
  while (!operator_stack.empty()) {
    polish_stack_.push(operator_stack.top());
    operator_stack.pop();
  }
}

}  // namespace s21
