#include "s21_parser.h"

namespace s21 {

/**
 * @brief Возвращает очередь токенов после разбора.
 *
 * @return Очередь токенов после разбора выражения.
 */
std::queue<Token> Parser::GetParsedInput() { return input_; };

/**
 * @brief Метод сброса состояния парсера.
 *
 * Очищает очередь токенов после разбора выражения.
 */
void Parser::Reset() {
  while (!input_.empty()) {
    input_.pop();
  }
}

/**
 * @brief Считывает слово из входной строки.
 *
 * @param input Входная строка.
 * @param start_index Индекс начала чтения слова.
 * @return Прочитанное слово.
 */
std::string Parser::ReadWord(const std::string& input,
                             size_t& start_index) const {
  std::regex word_regex("([a-z]+)");
  std::sregex_iterator regex_iterator = std::sregex_iterator(
      input.begin() + start_index, input.end(), word_regex);
  std::smatch match = *regex_iterator;
  start_index += match.length();
  return match.str();
}

/**
 * @brief Считывает число из входной строки.
 *
 * @param input Входная строка.
 * @param start_index Индекс начала чтения числа.
 * @return Прочитанное число.
 */
std::string Parser::ReadNumber(const std::string& input,
                               size_t& start_index) const {
  // std::regex word_regex("\\d+([.]\\d+)?(e([-+])?\\d+)?");
  std::regex word_regex("\\d*(\\.\\d+|\\d+\\.?)([e][-+]?\\d+)?");
  std::sregex_iterator regex_iterator = std::sregex_iterator(
      input.begin() + start_index, input.end(), word_regex);
  std::smatch match = *regex_iterator;
  start_index += match.length();
  return match.str();
}

/**
 * @brief Считывает начальную точку числа из входной строки.
 *
 * @param input Входная строка.
 * @param start_index Индекс начальной точки числа.
 * @return Начальная точка числа.
 */
std::string Parser::ReadNumberStartPoint(const std::string& input,
                                         size_t& start_index) const {
  std::regex word_regex("\\d+(e([-+])?\\d+)?");
  std::sregex_iterator regex_iterator = std::sregex_iterator(
      input.begin() + start_index, input.end(), word_regex);
  std::smatch match = *regex_iterator;
  start_index += match.length() + 1;
  return match.str();
}

/**
 * @brief Добавляет токен в очередь.
 *
 * @param token Строковое представление токена.
 * @param token_map Карта токенов для разбора выражения.
 */
void Parser::PushToken(std::string token,
                       std::map<std::string, Token> token_map) {
  auto token_map_iterator = token_map.find(token);
  if (token_map_iterator == token_map.end()) {
    throw std::logic_error("Incorrect symbol: " + token);
  }
  Parser::input_.push(token_map_iterator->second);
}

/**
 * @brief Добавляет токен числа в очередь.
 *
 * @param token Строковое представление токена.
 */
void Parser::PushTokenNumber(std::string token) {
  double number_value;
  number_value = std::stod(token);
  Token number_token;
  number_token.MakeNumber(token, number_value);
  // Token number_token = Token::MakeNumber(token, number_value);
  Parser::input_.push(number_token);
}

/**
 * @brief Разбирает входное выражение на токены.
 *
 * @param input_expression Входное арифметическое выражение.
 * @param token_map Карта токенов для разбора выражения.
 */
void Parser::Parse(const std::string& input_expression,
                   const std::map<std::string, Token>& token_map) {
  std::string token;
  size_t start_index = 0;
  while (start_index < input_expression.length()) {
    char ch = input_expression[start_index];
    if (std::isalpha(ch)) {
      if (ch == 'x') {
        token = 'x';
        start_index++;
      } else {
        token = Parser::ReadWord(input_expression, start_index);
      }
      PushToken(token, token_map);
    } else if (std::isdigit(ch)) {
      token = Parser::ReadNumber(input_expression, start_index);
      PushTokenNumber(token);
    } else if (ch == '.' && start_index + 1 < input_expression.length() &&
               std::isdigit(input_expression[start_index + 1])) {
      token =
          "0." + Parser::ReadNumberStartPoint(input_expression, start_index);
      PushTokenNumber(token);
    } else {
      token = ch;
      start_index++;
      PushToken(token, token_map);
    }
  }
}

}  // namespace s21