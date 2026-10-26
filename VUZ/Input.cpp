#include "Input.h"
#include "VuzException.h"
#include <iostream>

string readLine(const string& prompt)
{
    string s;
    cout << prompt;
    if (!getline(cin, s))
        throw VuzException("Ошибка: ввод прерван");
    return s;
}

int readInt(const string& prompt)
{
    string s = readLine(prompt);
    size_t pos = 0;
    int value;
    try
    {
        value = stoi(s, &pos);
    }
    catch (...)
    {
        throw VuzException("Ошибка: нужно ввести целое число");
    }
    if (pos != s.size())
        throw VuzException("Ошибка: нужно ввести целое число");
    return value;
}

double readDouble(const string& prompt)
{
    string s = readLine(prompt);
    for (size_t i = 0; i < s.size(); i++)
        if (s[i] == ',')
            s[i] = '.';
    size_t pos = 0;
    double value;
    try
    {
        value = stod(s, &pos);
    }
    catch (...)
    {
        throw VuzException("Ошибка: нужно ввести число");
    }
    if (pos != s.size())
        throw VuzException("Ошибка: нужно ввести число");
    return value;
}
