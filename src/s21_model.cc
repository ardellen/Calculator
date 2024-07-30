#include "s21_model.h"

namespace s21 {

/**
 * @brief Сбрасывает значения переменных класса в начальное состояние.
 */
void Model::Reset() {
  answer_ = 0;
  x_value_ = NAN;
  parser_.Reset();
  calculator_.Reset();
  validator_.Reset();
  converter_.Reset();
}

/**
 * @brief Возвращает текущее значение ответа.
 *
 * @return Текущее значение ответа.
 */
double Model::GetAnswer() const { return answer_; }

/**
 * @brief Устанавливает значение переменной x.
 *
 * @param x_value Новое значение переменной x.
 */
void Model::SetXValue(double x_value) { x_value_ = x_value; }

/**
 * @brief Возвращает текущее значение переменной x.
 *
 * @return Текущее значение переменной x.
 */
double Model::GetXValue() const { return x_value_; }

/**
 * @brief Преобразует строку в нижний регистр.
 *
 * @param str Входная строка.
 * @return Строка в нижнем регистре.
 */
std::string Model::ConvertToLowercase(const std::string& str) {
  std::string copy_str = str;
  std::transform(str.begin(), str.end(), copy_str.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return copy_str;
}

std::vector<std::pair<double, double>> Model::CalculateGraph(
    const GraphParams& params) {
  Reset();
  if (params.formula.empty()) {
    throw std::invalid_argument("Input expression is empty");
  }
  std::vector<std::pair<double, double>> result;
  std::string copy_str = ConvertToLowercase(params.formula);
  parser_.Parse(copy_str, token_map_manager_.GetTokenMap());
  validator_.Validate(parser_.GetParsedInput());

  for (double x = params.xMin; x <= params.xMax; x += params.step) {
    converter_.ConvertPolishNotation(validator_.GetValidInput(), x);
    double y = calculator_.Calculation(converter_.GetPolishNotation());
    if (y >= params.yMin && y <= params.yMax) {
      result.emplace_back(x, y);
    }
  }
  return result;
}

/**
 * @brief Вычисляет ответ на основе входного выражения и значения переменной
 * x.
 *
 * @param input_expression Входное арифметическое выражение.
 * @param input_x Значение переменной x.
 */
void Model::CalculateAnswer(const std::string& input_expression,
                            double input_x) {
  Reset();
  if (!std::isnan(input_x)) {
    SetXValue(input_x);
  } else {
    throw std::logic_error("Incorrect x value");
  }
  if (input_expression.empty()) {
    throw std::invalid_argument("Input expression is empty");
  }
  std::string copy_str = ConvertToLowercase(input_expression);
  parser_.Parse(copy_str, token_map_manager_.GetTokenMap());
  validator_.Validate(parser_.GetParsedInput());
  converter_.ConvertPolishNotation(validator_.GetValidInput(), x_value_);
  answer_ = calculator_.Calculation(converter_.GetPolishNotation());
}

}  // namespace s21