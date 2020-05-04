//
// Created by lyubaxapro on 01.05.20.
//

#ifndef OOP_SECOND_ERRORS_H
#define OOP_SECOND_ERRORS_H

#include <exception>

class BaseError : public std::exception
{
public:
    const char* what() const noexcept override {
        return "Some error was catched";
    }

};

class MemError : public BaseError
{
    const char* what() const noexcept override {
        return "A memory allocation error";
    }
};

class RangeError : public BaseError
{
    const char* what() const noexcept override {
        return "List is out of range";
    }
};
 // todo удалить несипользуемые ошибки
class CmpIterError : public BaseError
{
public:

    const char* what() const noexcept override {
        return "Comparing iterators with different sources";
    }
};

class EmptyError : public BaseError
{
public:

    const char* what() const noexcept override {
        return "Attempt to work with empty list or empty element";
    }
};
#endif //OOP_SECOND_ERRORS_H
