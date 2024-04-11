#pragma once

#include <string>
#include <exception>

class CoreInitializationException : public std::exception
{
public:
    CoreInitializationException(const string message) : message(message.c_str()) {}
    CoreInitializationException(const char *message) : message(message) {}

    virtual const char *what() const throw()
    {
        return message;
    }

    const char *message;
};
