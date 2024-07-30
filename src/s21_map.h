#ifndef S21_MAP_H
#define S21_MAP_H

#include <map>

#include "s21_token.h"

namespace s21 {
/**
 * @brief Класс TokenMapManager управляет картой токенов для парсинга выражений.
 *
 * Этот класс отвечает за создание и управление картой токенов, которая
 * используется в парсере для анализа входных выражений.
 */
class TokenMapManager {
 public:
  /**
   * @brief Конструктор класса TokenMapManager.
   *
   * Создает объект класса TokenMapManager и инициализирует карту токенов.
   */
  TokenMapManager() { CreateTokenMap(); }

  /**
   * @brief Получает ссылку на карту токенов.
   *
   * @return Ссылка на карту токенов.
   */
  std::map<std::string, Token>& GetTokenMap() { return token_map_; }

 private:
  /**
   * @brief Очищает карту токенов.
   */
  void ClearTokenMap();

  /**
   * @brief Создает карту токенов.
   *
   * Создает карту токенов, заполняя ее соответствующими значениями для каждого
   * токена.
   */
  void CreateTokenMap();

  std::map<std::string, Token>
      token_map_; /**< Карта токенов для парсинга выражений. */
};

}  // namespace s21

#endif  // S21_MAP_H
