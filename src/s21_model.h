#ifndef S21_MODEL_H
#define S21_MODEL_H

#include <sstream>
#include <vector>

#include "s21_calculation.h"
#include "s21_helpers.h"
#include "s21_map.h"
#include "s21_parser.h"
#include "s21_polish_notation.h"
#include "s21_token.h"
#include "s21_validator.h"

namespace s21 {

/**
 * @brief Класс Model представляет собой модель калькулятора.
 *
 * Этот класс отвечает за выполнение вычислений и управление данными
 * в рамках калькулятора. Включает в себя методы для вычисления ответа
 * по входным данным и управления значением переменной x.
 */
class Model {
 public:
  /**
   * @brief Вычисляет ответ на основе входного выражения и значения переменной
   * x.
   *
   * @param input_expression Входное арифметическое выражение.
   * @param input_x Значение переменной x.
   */
  void CalculateAnswer(const std::string& input_expression, double input_x);

  /**
   * @brief Возвращает текущее значение ответа.
   *
   * @return Текущее значение ответа.
   */
  double GetAnswer() const;

  /**
   * @brief Устанавливает значение переменной x.
   *
   * @param x_value Новое значение переменной x.
   */
  void SetXValue(double x_value);

  /**
   * @brief Возвращает текущее значение переменной x.
   *
   * @return Текущее значение переменной x.
   */
  double GetXValue() const;

  /**
   * @brief Вычисляет значения x и y для построения графика заданной функции.
   *
   * @return Вектор пар значений x и y.
   */
  std::vector<std::pair<double, double>> CalculateGraph(
      const GraphParams& params);

  /**
   * @brief Сбрасывает значения переменных класса в начальное состояние.
   */
  void Reset();

 private:
  /**
   * @brief Преобразует строку в нижний регистр.
   *
   * @param str Входная строка.
   * @return Строка в нижнем регистре.
   */
  std::string ConvertToLowercase(const std::string& str);

  TokenMapManager token_map_manager_; /**< Менеджер токенов. */
  Parser parser_; /**< Парсер для анализа входных данных. */
  Validator validator_; /**< Валидатор для проверки корректности ввода. */
  Calculator calculator_; /**< Калькулятор для выполнения вычислений. */
  Converter converter_; /**< Конверетер в польскую нотацию. */
  double x_value_{NAN}; /**< Значение переменной x. */
  double answer_{NAN};  /**< Текущий ответ. */
};

}  // namespace s21

#endif
