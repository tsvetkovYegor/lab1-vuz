#include "VuzException.h"

VuzException::VuzException(const string& message) : message(message)
{
}

const char* VuzException::what() const noexcept
{
    return message.c_str();
}
