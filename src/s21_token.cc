#include "s21_model.h"

namespace s21 {

/**
 * @brief Конструктор класса Token.
 *
 * @param name Имя токена.
 * @param priority Приоритет токена.
 * @param associativity Ассоциативность токена.
 * @param type Тип токена.
 * @param function Функция токена (по умолчанию nullptr).
 */
Token::Token(const std::string& name, Priority priority,
             Associativity associativity, Type type,
             function_variant function) {
  name_ = name;
  priority_ = priority;
  associativity_ = associativity;
  type_ = type;
  function_ = function;
}

/**
 * @brief Преобразует токен в число.
 *
 * @param name Имя числа.
 * @param value Значение числа.
 */
void Token::MakeNumber(std::string name, double value) {
  Token result(name, kDefault, kNone, kNumber, value);
  *this = result;
}

/**
 * @brief Преобразует токен в унарный оператор отрицания.
 */
void Token::MakeUnaryNegation() {
  Token result("negate", kUnaryOp, kRight, kUnaryOperator,
               std::negate<double>());
  *this = result;
}

/**
 * @brief Возвращает имя токена.
 *
 * @return Строка с именем токена.
 */
std::string Token::GetName() const noexcept { return name_; };

/**
 * @brief Возвращает приоритет токена.
 *
 * @return Приоритет токена.
 */
Priority Token::GetPriority() const noexcept { return priority_; };

/**
 * @brief Возвращает ассоциативность токена.
 *
 * @return Ассоциативность токена.
 */
Associativity Token::GetAssociativity() const noexcept {
  return associativity_;
};

/**
 * @brief Возвращает тип токена.
 *
 * @return Тип токена.
 */
Type Token::GetType() const noexcept { return type_; };

/**
 * @brief Возвращает вариант функции токена.
 *
 * @return Ссылка на вариант функции токена.
 */
const function_variant& Token::GetFunction() const { return function_; }

}  // namespace s21