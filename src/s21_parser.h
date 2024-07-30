#ifndef S21_PARSER_H
#define S21_PARSER_H

#include <list>
#include <queue>
#include <regex>

#include "s21_token.h"

namespace s21 {
/**
 * @brief Класс Parser представляет собой парсер для анализа входного выражения.
 *
 * Этот класс отвечает за разбор входного арифметического выражения на токены,
 * которые могут быть использованы для выполнения вычислений.
 */
class Parser {
 public:
  /**
   * @brief Метод сброса состояния парсера.
   *
   * Очищает очередь токенов после разбора выражения.
   */
  void Reset();

  /**
   * @brief Разбирает входное выражение на токены.
   *
   * @param input_expression Входное арифметическое выражение.
   * @param token_map Карта токенов для разбора выражения.
   */
  void Parse(const std::string& input_expression,
             const std::map<std::string, Token>& token_map);

  /**
   * @brief Возвращает очередь токенов после разбора.
   *
   * @return Очередь токенов после разбора выражения.
   */
  std::queue<Token> GetParsedInput();

 private:
  /**
   * @brief Добавляет токен числа в очередь.
   *
   * @param token Строковое представление токена.
   */
  void PushTokenNumber(std::string token);

  /**
   * @brief Добавляет токен в очередь.
   *
   * @param token Строковое представление токена.
   * @param token_map Карта токенов для разбора выражения.
   */
  void PushToken(std::string token, std::map<std::string, Token> token_map);

  /**
   * @brief Считывает начальную точку числа из входной строки.
   *
   * @param input Входная строка.
   * @param start_index Индекс начальной точки числа.
   * @return Начальная точка числа.
   */
  std::string ReadNumberStartPoint(const std::string& input,
                                   size_t& start_index) const;

  /**
   * @brief Считывает число из входной строки.
   *
   * @param input Входная строка.
   * @param start_index Индекс начала чтения числа.
   * @return Прочитанное число.
   */
  std::string ReadNumber(const std::string& input, size_t& start_index) const;

  /**
   * @brief Считывает слово из входной строки.
   *
   * @param input Входная строка.
   * @param start_index Индекс начала чтения слова.
   * @return Прочитанное слово.
   */
  std::string ReadWord(const std::string& input, size_t& start_index) const;

  std::queue<Token> input_; /**< Очередь токенов после разбора выражения. */
};

}  // namespace s21

#endif  // S21_PARSER_H
