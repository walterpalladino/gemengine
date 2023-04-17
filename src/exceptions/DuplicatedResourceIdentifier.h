#pragma once

#include <exception>

class DuplicatedResourceIdentifier : public std::exception
{
public:
    DuplicatedResourceIdentifier(const char *message) : message(message) {}

    virtual const char *what() const throw()
    {
        return message;
    }

    const char *message;
};
