#include "s21_map.h"

namespace s21 {

/**
 * @brief Создает карту токенов.
 *
 * Этот метод создает карту токенов, заполняя ее соответствующими значениями
 * для каждого токена.
 */

void TokenMapManager::CreateTokenMap() {
  token_map_.clear();
  using std::initializer_list;
  using std::pair;
  using std::string;
  using namespace s21;
  initializer_list<pair<const string, Token>> list = {
      {" ", Token("space", kDefault, kNone, kSpace, nullptr)},
      {"x", Token("x", kDefault, kNone, kNumber, nullptr)},
      {"(", Token("(", kDefault, kNone, kOpenBracket, nullptr)},
      {")", Token(")", kDefault, kNone, kCloseBracket, nullptr)},
      {"+", Token("+", kLow, kLeft, kBinaryOperator, std::plus<double>())},
      {"-", Token("-", kLow, kLeft, kBinaryOperator, std::minus<double>())},
      {"*",
       Token("*", kMedium, kLeft, kBinaryOperator, std::multiplies<double>())},
      {"/",
       Token("/", kMedium, kLeft, kBinaryOperator, std::divides<double>())},
      {"^", Token("^", kHigh, kRight, kBinaryOperator, powl)},
      {"mod", Token("mod", kMedium, kLeft, kBinaryOperator, fmodl)},
      {"cos", Token("cos", kFunction, kNone, kUnaryOperator, cosl)},
      {"sin", Token("sin", kFunction, kNone, kUnaryOperator, sinl)},
      {"tan", Token("tan", kFunction, kNone, kUnaryOperator, tanl)},
      {"acos", Token("acos", kFunction, kNone, kUnaryOperator, acosl)},
      {"asin", Token("asin", kFunction, kNone, kUnaryOperator, asinl)},
      {"atan", Token("atan", kFunction, kNone, kUnaryOperator, atanl)},
      {"sqrt", Token("sqrt", kFunction, kNone, kUnaryOperator, sqrtl)},
      {"ln", Token("ln", kFunction, kNone, kUnaryOperator, logl)},
      {"log", Token("log", kFunction, kNone, kUnaryOperator, log10l)},
      {"e", Token("e", kDefault, kNone, kNumber, M_E)},
      {"pi", Token("pi", kDefault, kNone, kNumber, M_PI)},
      {"inf", Token("inf", kDefault, kNone, kNumber, INFINITY)},
  };
  token_map_.insert(list);
}

/**
 * @brief Очищает карту токенов.
 *
 * Этот метод очищает карту токенов, удаляя все записи из нее.
 */

void TokenMapManager::ClearTokenMap() { token_map_.clear(); }

}  // namespace s21
