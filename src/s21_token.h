#ifndef S21_TOKEN_H
#define S21_TOKEN_H

#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <variant>

namespace s21 {

/**
 * @brief Пространство имен s21 содержит определения для калькулятора.
 *
 * Это пространство имен содержит определения типов, функций и классов,
 * необходимых для реализации калькулятора.
 */

using unary_function = std::function<double(double)>;
using binary_function = std::function<double(double, double)>;
using function_variant =
    std::variant<double, unary_function, binary_function, nullptr_t>;

/**
 * @brief Перечисление Priority определяет приоритет операторов.
 */
enum Priority {
  kDefault,  /**< По умолчанию */
  kLow,      /**< Низкий приоритет (+ -) */
  kMedium,   /**< Средний приоритет (* / mod) */
  kHigh,     /**< Высокий приоритет (^) */
  kUnaryOp,  /**< Унарные операторы */
  kFunction, /**< Функции */
};

/**
 * @brief Перечисление Associativity определяет ассоциативность операторов.
 */
enum Associativity {
  kNone,  /**< Не ассоциативный */
  kRight, /**< Правоассоциативный */
  kLeft,  /**< Левоассоциативный */
};

/**
 * @brief Перечисление Type определяет типы токенов.
 */
enum Type {
  kNumber,         /**< Число */
  kBinaryOperator, /**< Бинарный оператор */
  kUnaryOperator,  /**< Унарный оператор */
  kUnaryFunction,  /**< Унарная функция */
  kOpenBracket,    /**< Открывающая скобка */
  kCloseBracket,   /**< Закрывающая скобка */
  kSpace,          /**< Пробел */
  kNumTokenTypes,  /**< Количество типов токенов */
};

/**
 * @brief Шаблон структуры overloaded позволяет создавать объекты, которые могут
 * быть вызваны как функции с различными перегрузками.
 *
 * Этот шаблон предоставляет возможность создавать объекты, которые являются
 * перегруженными функциями. Объекты этой структуры могут быть вызваны как
 * функции с различными перегрузками, и компилятор будет выбирать наиболее
 * подходящую перегрузку в зависимости от переданных аргументов.
 *
 * Пример использования:
 * @code
 * auto my_func = overloaded {
 *     [](int x) { return x * 2; },
 *     [](double x) { return x * 3.14; }
 * };
 *
 * int result1 = my_func(10);      // Вызывается первая перегрузка.
 * double result2 = my_func(3.5);  // Вызывается вторая перегрузка.
 * @endcode
 */
template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};

/**
 * @brief Шаблон deduction guide overloaded позволяет выводить типы параметров
 * шаблона.
 *
 * Этот deduction guide позволяет выводить типы параметров шаблона для создания
 * объектов overloaded.
 */
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

/**
 * @brief Класс Token представляет собой токен для использования в калькуляторе.
 *
 * Каждый токен имеет имя, приоритет, ассоциативность, тип и возможно функцию.
 */
class Token {
 public:
  /**
   * @brief Конструктор класса Token.
   */
  Token() = default;

  /**
   * @brief Конструктор класса Token.
   *
   * @param name Имя токена.
   * @param priority Приоритет токена.
   * @param associativity Ассоциативность токена.
   * @param type Тип токена.
   * @param function Функция токена (по умолчанию nullptr).
   */
  Token(const std::string& name, Priority priority, Associativity associativity,
        Type type, function_variant function = nullptr);

  // Геттеры
  /**
   * @brief Возвращает имя токена.
   *
   * @return Строка с именем токена.
   */
  std::string GetName() const noexcept;

  /**
   * @brief Возвращает приоритет токена.
   *
   * @return Приоритет токена.
   */
  Priority GetPriority() const noexcept;

  /**
   * @brief Возвращает ассоциативность токена.
   *
   * @return Ассоциативность токена.
   */
  Associativity GetAssociativity() const noexcept;

  /**
   * @brief Возвращает тип токена.
   *
   * @return Тип токена.
   */
  Type GetType() const noexcept;

  /**
   * @brief Возвращает вариант функции токена.
   *
   * @return Ссылка на вариант функции токена.
   */
  const function_variant& GetFunction() const;

  /**
   * @brief Преобразует токен в число.
   *
   * @param name Имя числа.
   * @param value Значение числа.
   */
  void MakeNumber(std::string name, double value);

  /**
   * @brief Преобразует токен в унарный оператор отрицания.
   */
  void MakeUnaryNegation();

 private:
  std::string name_;            /**< Имя токена. */
  Priority priority_;           /**< Приоритет токена. */
  Associativity associativity_; /**< Ассоциативность токена. */
  Type type_;                   /**< Тип токена. */
  function_variant function_; /**< Функция токена. */
};

}  // namespace s21

#endif  // S21_TOKEN_H