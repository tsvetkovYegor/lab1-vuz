#pragma once
#include <iostream>
#include <string>

using namespace std;

// Абстрактный базовый класс - человек в ВУЗе
class Base
{
protected:
    string fio;

public:
    Base();
    Base(const string& fio);
    Base(const Base& other);
    virtual ~Base();

    string getFio() const;
    void setFio(const string& fio);

    virtual string getType() const = 0;            // тип объекта
    virtual Base* clone() const = 0;               // копия объекта
    virtual void input() = 0;                      // ввод с клавиатуры
    virtual void edit() = 0;                       // изменение данных
    virtual void print(ostream& out) const = 0;    // вывод на экран
    virtual void save(ostream& out) const = 0;     // запись в файл
    virtual void load(istream& in) = 0;            // чтение из файла

    friend ostream& operator<<(ostream& out, const Base& obj);
};
