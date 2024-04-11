#pragma once

#include <string>
#include <exception>

class DuplicatedResourceIdentifier : public std::exception
{
public:
    DuplicatedResourceIdentifier(const string message) : message(message.c_str()) {}
    DuplicatedResourceIdentifier(const char *message) : message(message) {}

    virtual const char *what() const throw()
    {
        return message;
    }

    const char *message;
};
