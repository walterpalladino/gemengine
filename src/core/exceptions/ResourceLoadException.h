#pragma once

#include <string>
#include <exception>

class ResourceLoadException : public std::exception
{
public:
    ResourceLoadException(const string message) : message(message.c_str()) {}
    ResourceLoadException(const char *message) : message(message) {}

    virtual const char *what() const throw()
    {
        return message;
    }

    const char *message;
};
