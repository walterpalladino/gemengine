#pragma once

#include <string>
#include <exception>

class JSONParseException : public std::exception
{
public:
    JSONParseException(const string message) : message(message.c_str()) {}
    JSONParseException(const char *message) : message(message) {}

    virtual const char *what() const throw()
    {
        return message;
    }

    const char *message;
};
