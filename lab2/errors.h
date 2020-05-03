//
// Created by lyubaxapro on 01.05.20.
//

#ifndef OOP_SECOND_ERRORS_H
#define OOP_SECOND_ERRORS_H

#include <exception>

//todo : класс c большой буквы
class baseError : public std::exception
{
public:
    const char* what() const noexcept override {
        return "Some error was catched";
    }

};

class memError : public baseError
{
    const char* what() const noexcept override {
        return "A memory allocation error";
    }
};

class rangeError : public baseError
{
    const char* what() const noexcept override {
        return "List is out of range";
    }
};

class cmpIterError : public baseError
{
public:

    const char* what() const noexcept override {
        return "Comparing iterators with different sources";
    }
};

class emptyError : public baseError
{
public:

    const char* what() const noexcept override {
        return "Attempt to work with empty list or empty element";
    }
};
#endif //OOP_SECOND_ERRORS_H
