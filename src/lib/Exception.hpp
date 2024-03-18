#ifndef TM_LIB_EXCEPTION_H_
#define TM_LIB_EXCEPTION_H_

#include <exception>
#include <string>

namespace Exception
{
    class InactiveMachine : public std::exception
    {
    public:
        std::string what()
        {
            return "Машина Тьюринга закончила работу";
        }
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
        std::string what() { return "Невозможно удалить состояние из пустой таблицы"; }
    };
    class UnallowedSymbol : public std::exception
    {
    public:
        std::string what() { return "Разрешены только символы из ASCII таблицы, которые больше 32, кроме цифр и '!', '<' и '>'"; }
    };
    class UnknownSymbol : public std::exception
    {
    public:
        std::string what() { return "Введен символ, которого нет в алфавите"; }
    };
};

#endif // TM_LIB_EXCEPTION_H_