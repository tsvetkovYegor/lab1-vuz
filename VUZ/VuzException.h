#pragma once
#include <exception>
#include <string>

using namespace std;

// Собственный класс исключений программы
class VuzException : public exception
{
private:
    string message;

public:
    VuzException(const string& message);
    const char* what() const noexcept override;
};
