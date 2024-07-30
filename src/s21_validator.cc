#include "s21_validator.h"

namespace s21 {

/**
 * @brief Возвращает валидированную последовательность токенов.
 *
 * @return Список токенов, прошедших валидацию.
 */
std::list<Token> Validator::GetValidInput() { return validated_input_; }

/**
 * @brief Вставляет неявные умножения в последовательность токенов.
 *
 * @param present_token Текущий токен.
 * @param previous_token Предыдущий токен.
 */
void Validator::InsertMultiplication(Token present_token,
                                     Token previous_token) {
  if ((previous_token.GetType() == Type::kNumber &&
       present_token.GetName() == "x") ||
      (present_token.GetType() == Type::kNumber &&
       previous_token.GetName() == "x") ||
      (previous_token.GetName() == ")" && present_token.GetName() == "(") ||
      (previous_token.GetName() == ")" &&
       present_token.GetType() == Type::kNumber) ||
      (previous_token.GetType() == Type::kNumber &&
       present_token.GetName() == "(") ||
      (previous_token.GetType() == Type::kNumber &&
       present_token.GetPriority() == kFunction) ||
      (previous_token.GetName() == ")" &&
       present_token.GetPriority() == kFunction)) {
    Token multiplication("*", kMedium, kLeft, kBinaryOperator,
                         std::multiplies<double>());
    validated_input_.push_back(multiplication);
  }
}

/**
 * @brief Проводит валидацию отдельных токенов.
 */
void Validator::ValidateTokens() {
  auto it_i = validated_input_.begin();
  if (it_i->GetType() == kBinaryOperator || it_i->GetType() == kCloseBracket) {
    throw std::logic_error("Incorrect first token");
  }
  for (; it_i != validated_input_.end(); ++it_i) {
    auto it_j = std::next(it_i);
    // std::cout << it_i->GetName() << std::endl;
    if ((it_j != validated_input_.end() &&
         !kAdjacencyMatrix_[it_i->GetType()][it_j->GetType()])) {
      // std::cout << it_j->GetType() << std::endl;
      throw std::logic_error("Incompatible tokens found " + it_i->GetName() +
                             " and " + it_j->GetName());
    }
  }
  if (!(validated_input_.back().GetType() == kNumber ||
        validated_input_.back().GetType() == kCloseBracket)) {
    // std::cout << "! " << validated_input_.back().GetName() << " ! ";
    throw std::logic_error("Incorrect last token");
  }
}

/**
 * @brief Метод сброса состояния корректора.
 *
 * Очищает лист токенов после коррекции выражения.
 */
void Validator::Reset() { validated_input_.clear(); }

/**
 * @brief Проводит валидацию последовательности токенов.x
 *
 * @param input_parsed Очередь токенов, полученных после парсинга.
 */
void Validator::Validate(const std::queue<Token> input_parsed) {
  std::queue<Token> copy_input = input_parsed;
  Token prev_token("space", kDefault, kNone, kSpace, nullptr);
  int brackets = 0;
  while (!copy_input.empty()) {
    Token token = copy_input.front();
    copy_input.pop();
    if (token.GetName() == "space") {
      continue;
    }
    if (prev_token.GetPriority() == 5 && token.GetName() != "(") {
      Token openBracket("(", kDefault, kNone, kOpenBracket, nullptr);
      validated_input_.push_back(openBracket);
      brackets++;
    }
    if (token.GetPriority() == 1 &&
        !(prev_token.GetType() == 0 || prev_token.GetType() == 5)) {
      if (token.GetName() == "-")
        token.MakeUnaryNegation();
      else
        continue;
    }
    if (token.GetName() == "(") brackets++;
    if (token.GetName() == ")") brackets--;
    InsertMultiplication(token, prev_token);
    prev_token = token;
    validated_input_.push_back(token);
  }
  if (brackets < 0) throw std::logic_error("Incorrect number of open brackets");
  while (brackets > 0) {
    Token closeBracket(")", kDefault, kNone, kCloseBracket, nullptr);
    validated_input_.push_back(closeBracket);
    brackets--;
  }
  if (validated_input_.empty()) {
    throw std::invalid_argument("Input expression is empty");
  }
  ValidateTokens();
}

}  // namespace s21