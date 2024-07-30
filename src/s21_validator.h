#ifndef S21_VALIDATOR_H
#define S21_VALIDATOR_H

#include <list>
#include <queue>

#include "s21_token.h"

namespace s21 {

/**
 * @brief Класс Validator представляет собой валидатор для проверки корректности
 * токенов.
 *
 * Этот класс отвечает за проверку корректности последовательности токенов,
 * полученных после парсинга входного выражения.
 */
class Validator {
 public:
  /**
   * @brief Проводит валидацию последовательности токенов.
   *
   * @param input_parsed Очередь токенов, полученных после парсинга.
   */
  void Validate(const std::queue<Token> input_parsed);

  /**
   * @brief Возвращает валидированную последовательность токенов.
   *
   * @return Список токенов, прошедших валидацию.
   */
  std::list<Token> GetValidInput();

  /**
   * @brief Метод сброса состояния корректора.
   *
   * Очищает лист токенов после коррекции выражения.
   */
  void Reset();

 private:
  /**
   * @brief Проводит валидацию отдельных токенов.
   */
  void ValidateTokens();

  /**
   * @brief Вставляет неявные умножения в последовательность токенов.
   *
   * @param present_token Текущий токен.
   * @param previous_token Предыдущий токен.
   */
  void InsertMultiplication(Token present_token, Token previous_token);

  std::list<Token>
      validated_input_; /**< Валидированная последовательность токенов. */
  static constexpr bool kAdjacencyMatrix_[kNumTokenTypes][kNumTokenTypes] = {
      {0, 1, 0, 0, 0, 1, 0},  // kNumber
      {1, 0, 1, 1, 1, 0, 0},  // kBinaryOperator
      {1, 0, 1, 1, 1, 0, 0},  // kUnaryOperator
      {0, 0, 0, 0, 1, 0, 0},  // kUnaryFunction
      {1, 0, 1, 1, 1, 0, 0},  // kOpenBracket
      {0, 1, 0, 0, 0, 1, 0},  // kCloseBracket
      {0, 0, 0, 0, 0, 0, 0},  // kSpace
  }; /**< Матрица смежности для валидации токенов. */
};

}  // namespace s21

#endif  // S21_VALIDATOR_H