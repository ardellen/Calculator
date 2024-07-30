#include "s21_controller.h"

namespace s21 {

/**
 * @brief Выполняет вычисление выражения с заданным значением переменной.
 *
 * @param input Строка, содержащая математическое выражение для вычисления.
 * @param x Значение переменной x, используемое в выражении.
 * @return double Результат вычисления выражения.
 */
double Controller::Calculate(std::string input, double x) {
  model_->CalculateAnswer(input, x);
  double answer = model_->GetAnswer();
  return answer;
}

/**
 * @brief Вычисляет значения для построения графика на основе заданных
 * параметров.
 *
 * @param params Объект GraphParams, содержащий параметры для генерации данных
 * графика.
 * @return std::vector<std::pair<double, double>> Вектор пар значений (x, y),
 * представляющих точки графика.
 */
std::vector<std::pair<double, double>> Controller::CalculateGraph(
    const GraphParams& params) {
  return model_->CalculateGraph(params);
}

}  // namespace s21
