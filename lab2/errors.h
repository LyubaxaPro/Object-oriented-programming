//
// Created by lyubaxapro on 01.05.20.
//

#ifndef OOP_SECOND_ERRORS_H
#define OOP_SECOND_ERRORS_H

#include <exception>

class BaseError : public std::exception
{
public:
    explicit BaseError(
            const std::string& filename,
            const std::string& classname,
            const int line,
            const char *time,
            const std::string& info)
    {
        msg = "In: " + filename +
                "\n inside: " + classname +
                "\nat line: " + std::to_string(line) +
                "\nat: " + time +
                "\noccured: " + info;
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

class MemError : public BaseError
{
public:
    MemError(
            const std::string& filename,
            const std::string& classname,
            const int line,
            const char *time,
            const std::string& info = "A memory allocation error"
            ): BaseError(filename, classname, line, time, info){}
};

class RangeError : public BaseError
{
public:
    RangeError(
            const std::string& filename,
            const std::string& classname,
            const int line,
            const char *time,
            const std::string& info = "List is out of range"
    ): BaseError(filename, classname, line, time, info){}
};

class EmptyError : public BaseError
{
public:
    EmptyError(
            const std::string& filename,
            const std::string& classname,
            const int line,
            const char *time,
            const std::string& info = "Attempt to work with empty list or empty element"
                    ): BaseError(filename, classname, line, time, info){}

};
#endif //OOP_SECOND_ERRORS_H
