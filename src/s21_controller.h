#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <utility>

#include "s21_model.h"

namespace s21 {

/**
 * @brief Класс Controller управляет взаимодействием между пользовательским
 * интерфейсом и моделью данных.
 *
 * Класс предоставляет интерфейс для выполнения вычислений и получения данных о
 * графиках на основе входных параметров.
 */
class Controller {
 public:
  /**
   * @brief Конструктор класса Controller.
   *
   * @param m Указатель на объект Model, который используется для выполнения
   * вычислений.
   */
  Controller(Model *m) : model_(m){};

  /**
   * @brief Деструктор класса Controller.
   */
  ~Controller() = default;

  /**
   * @brief Выполняет вычисление выражения с заданным значением переменной.
   *
   * @param input Строка, содержащая математическое выражение для вычисления.
   * @param x Значение переменной x, используемое в выражении.
   * @return double Результат вычисления выражения.
   */
  double Calculate(std::string input, double x);

  /**
   * @brief Вычисляет значения для построения графика на основе заданных
   * параметров.
   *
   * @param params Объект GraphParams, содержащий параметры для генерации данных
   * графика.
   * @return std::vector<std::pair<double, double>> Вектор пар значений (x, y),
   * представляющих точки графика.
   */
  std::vector<std::pair<double, double>> CalculateGraph(
      const GraphParams &params);

 private:
  Model *model_;  ///< Указатель на модель, используемую для вычислений.
};

}  // namespace s21

#endif