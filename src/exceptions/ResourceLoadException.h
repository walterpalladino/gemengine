#pragma once

#include <exception>

class ResourceLoadException : public std::exception
{
public:
    ResourceLoadException(const char *message) : message(message) {}

    virtual const char *what() const throw()
    {
        return message;
    }

    const char *message;
};
