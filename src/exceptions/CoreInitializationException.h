#pragma once

#include <exception>

class CoreInitializationException : public std::exception
{
public:
    CoreInitializationException(const char *message) : message(message) {}

    virtual const char *what() const throw()
    {
        return message;
    }

    const char *message;
};
