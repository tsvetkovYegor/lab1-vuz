#include "Admin.h"
#include "VuzException.h"
#include "Input.h"

Admin::Admin() : Base(), position("Не указана"), phone("Не указан"),
                 area("Не указана")
{
    cout << "Admin: вызван конструктор без параметров" << endl;
}

Admin::Admin(const string& fio, const string& position, const string& phone,
             const string& area) : Base(fio)
{
    cout << "Admin: вызван конструктор с параметрами" << endl;
    setPosition(position);
    setPhone(phone);
    setArea(area);
}

Admin::Admin(const Admin& other) : Base(other), position(other.position),
    phone(other.phone), area(other.area)
{
    cout << "Admin: вызван конструктор копирования" << endl;
}

Admin::~Admin()
{
    cout << "Admin: вызван деструктор" << endl;
}

string Admin::getPosition() const { return position; }
string Admin::getPhone() const { return phone; }
string Admin::getArea() const { return area; }

void Admin::setPosition(const string& position)
{
    if (position.empty())
        throw VuzException("Ошибка: должность не может быть пустой");
    this->position = position;
}

void Admin::setPhone(const string& phone)
{
    int digits = 0;
    for (size_t i = 0; i < phone.size(); i++)
    {
        char c = phone[i];
        if (c >= '0' && c <= '9')
            digits++;
        else if (c != '+' && c != '-' && c != ' ' && c != '(' && c != ')')
            throw VuzException("Ошибка: телефон может содержать только цифры, +, -, скобки и пробелы");
    }
    if (digits < 5)
        throw VuzException("Ошибка: в телефоне должно быть не меньше 5 цифр");
    this->phone = phone;
}

void Admin::setArea(const string& area)
{
    if (area.empty())
        throw VuzException("Ошибка: область ответственности не может быть пустой");
    this->area = area;
}

string Admin::getType() const
{
    return "Административный персонал";
}

Base* Admin::clone() const
{
    return new Admin(*this);
}

void Admin::input()
{
    setFio(readLine("Введите ФИО: "));
    setPosition(readLine("Введите должность: "));
    setPhone(readLine("Введите телефон: "));
    setArea(readLine("Введите область ответственности: "));
}

void Admin::edit()
{
    cout << "1 - ФИО" << endl;
    cout << "2 - Должность" << endl;
    cout << "3 - Телефон" << endl;
    cout << "4 - Область ответственности" << endl;
    int choice = readInt("Что изменить: ");
    switch (choice)
    {
    case 1: setFio(readLine("Новое ФИО: ")); break;
    case 2: setPosition(readLine("Новая должность: ")); break;
    case 3: setPhone(readLine("Новый телефон: ")); break;
    case 4: setArea(readLine("Новая область ответственности: ")); break;
    default: throw VuzException("Ошибка: нет такого пункта");
    }
}

void Admin::print(ostream& out) const
{
    out << "[" << getType() << "]" << endl;
    out << "ФИО: " << fio << endl;
    out << "Должность: " << position << endl;
    out << "Телефон: " << phone << endl;
    out << "Область ответственности: " << area << endl;
}

void Admin::save(ostream& out) const
{
    out << "ADMIN" << endl;
    out << fio << endl;
    out << position << endl;
    out << phone << endl;
    out << area << endl;
}

void Admin::load(istream& in)
{
    string s;
    getline(in, s); setFio(s);
    getline(in, s); setPosition(s);
    getline(in, s); setPhone(s);
    getline(in, s); setArea(s);
}

Admin& Admin::operator=(const Admin& other)
{
    if (this != &other)
    {
        fio = other.fio;
        position = other.position;
        phone = other.phone;
        area = other.area;
    }
    return *this;
}
