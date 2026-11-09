#include "Keeper.h"
#include "Student.h"
#include "Teacher.h"
#include "Admin.h"
#include "VuzException.h"
#include <fstream>

Keeper::Keeper() : items(nullptr), size(0), capacity(0)
{
    cout << "Keeper: вызван конструктор без параметров" << endl;
}

Keeper::Keeper(int capacity) : size(0)
{
    cout << "Keeper: вызван конструктор с параметрами" << endl;
    if (capacity < 0)
        throw VuzException("Ошибка: емкость не может быть отрицательной");
    this->capacity = capacity;
    items = (capacity > 0) ? new Base*[capacity] : nullptr;
}

Keeper::Keeper(const Keeper& other) : size(other.size), capacity(other.size)
{
    cout << "Keeper: вызван конструктор копирования" << endl;
    items = (size > 0) ? new Base*[size] : nullptr;
    for (int i = 0; i < size; i++)
        items[i] = other.items[i]->clone();
}

Keeper::~Keeper()
{
    cout << "Keeper: вызван деструктор" << endl;
    clear();
}

void Keeper::resize(int newCapacity)
{
    Base** newItems = new Base*[newCapacity];
    for (int i = 0; i < size; i++)
        newItems[i] = items[i];
    delete[] items;
    items = newItems;
    capacity = newCapacity;
}

int Keeper::getSize() const
{
    return size;
}

Base* Keeper::get(int index) const
{
    if (index < 0 || index >= size)
        throw VuzException("Ошибка: объекта с таким номером нет");
    return items[index];
}

void Keeper::add(Base* obj)
{
    if (obj == nullptr)
        throw VuzException("Ошибка: нельзя добавить пустой объект");
    if (size == capacity)
        resize(capacity == 0 ? 2 : capacity * 2);
    items[size] = obj;
    size++;
}

void Keeper::remove(int index)
{
    if (index < 0 || index >= size)
        throw VuzException("Ошибка: объекта с таким номером нет");
    delete items[index];
    for (int i = index; i < size - 1; i++)
        items[i] = items[i + 1];
    size--;
}

void Keeper::clear()
{
    for (int i = 0; i < size; i++)
        delete items[i];
    delete[] items;
    items = nullptr;
    size = 0;
    capacity = 0;
}

void Keeper::saveToFile(const string& fileName) const
{
    ofstream file(fileName);
    if (!file.is_open())
        throw VuzException("Ошибка: не удалось открыть файл для записи");
    file << size << endl;
    for (int i = 0; i < size; i++)
        items[i]->save(file);
    file.close();
}

void Keeper::loadFromFile(const string& fileName)
{
    ifstream file(fileName);
    if (!file.is_open())
        throw VuzException("Ошибка: не удалось открыть файл для чтения");

    clear();
    string s;
    int count;
    getline(file, s);
    try { count = stoi(s); }
    catch (const invalid_argument&) { throw VuzException("Ошибка: файл поврежден"); }

    for (int i = 0; i < count; i++)
    {
        getline(file, s);
        Base* obj;
        if (s == "STUDENT")
            obj = new Student();
        else if (s == "TEACHER")
            obj = new Teacher();
        else if (s == "ADMIN")
            obj = new Admin();
        else
            throw VuzException("Ошибка: неизвестный тип объекта в файле");

        try
        {
            obj->load(file);
        }
        catch (...)
        {
            delete obj;
            throw;
        }
        add(obj);
    }
    file.close();
}

Base* Keeper::operator[](int index) const
{
    return get(index);
}

Keeper& Keeper::operator+=(Base* obj)
{
    add(obj);
    return *this;
}

Keeper& Keeper::operator=(const Keeper& other)
{
    if (this != &other)
    {
        clear();
        size = other.size;
        capacity = other.size;
        items = (size > 0) ? new Base*[size] : nullptr;
        for (int i = 0; i < size; i++)
            items[i] = other.items[i]->clone();
    }
    return *this;
}

ostream& operator<<(ostream& out, const Keeper& k)
{
    if (k.size == 0)
    {
        out << "Список пуст" << endl;
        return out;
    }
    for (int i = 0; i < k.size; i++)
    {
        out << "--- Объект " << i + 1 << " ---" << endl;
        out << *k.items[i];
    }
    return out;
}
