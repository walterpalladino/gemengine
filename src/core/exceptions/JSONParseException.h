#pragma once

#include <exception>

class JSONParseException : public std::exception
{
public:
    JSONParseException(const char *message) : message(message) {}

    virtual const char *what() const throw()
    {
        return message;
    }

    const char *message;
};
