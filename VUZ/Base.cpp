#include "Base.h"
#include "VuzException.h"

Base::Base() : fio("Не указано")
{
    cout << "Base: вызван конструктор без параметров" << endl;
}

Base::Base(const string& fio)
{
    cout << "Base: вызван конструктор с параметрами" << endl;
    setFio(fio);
}

Base::Base(const Base& other) : fio(other.fio)
{
    cout << "Base: вызван конструктор копирования" << endl;
}

Base::~Base()
{
    cout << "Base: вызван деструктор" << endl;
}

string Base::getFio() const
{
    return fio;
}

void Base::setFio(const string& fio)
{
    if (fio.empty())
        throw VuzException("Ошибка: ФИО не может быть пустым");
    this->fio = fio;
}

ostream& operator<<(ostream& out, const Base& obj)
{
    obj.print(out);
    return out;
}
