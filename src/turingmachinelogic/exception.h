#pragma once
#include <exception>
#include <string>
namespace exception
{
  class InactiveMachine : public std::exception
  {
  public:
    std::string what() { return "Машина Тьюринга закончила работу"; }
  };
  class AlphabetIntersection : public std::exception
  {
  public:
    std::string what() { return "Введенные алфавиты пересекаются"; }
  };
  class BadFunction : public std::exception
  {
  public:
    std::string what() { return "Некорректная функция"; }
  };
  class DeleteNothing : public std::exception
  {
  public:
    std::string what() { return "В таблице должно быть хотя бы одно состояние"; }
  };
  class UnallowedSymbol : public std::exception
  {
  public:
    std::string what()
    {
      return "Разрешены только символы из ASCII таблицы, которые больше 32, "
             "кроме цифр и '!', '<' и '>'";
    }
  };
  class UnknownSymbol : public std::exception
  {
  public:
    std::string what() { return "Введен символ, которого нет в алфавите"; }
  };
  class SymbolNotFromAlphabetOnTape : public std::exception
  {
  public:
    std::string what()
    {
      return "Символ, которого нет в основном алфавите, остался на ленте";
    }
  };
}; // namespace exception