#pragma once
#include "Base.h"

// Контейнер для хранения объектов ВУЗа
class Keeper
{
private:
    Base** items;     // динамический массив указателей на объекты
    int size;         // сколько объектов хранится
    int capacity;     // сколько места выделено

    void resize(int newCapacity);

public:
    Keeper();
    Keeper(int capacity);
    Keeper(const Keeper& other);
    ~Keeper();

    int getSize() const;
    Base* get(int index) const;

    void add(Base* obj);
    void remove(int index);
    void clear();

    void saveToFile(const string& fileName) const;
    void loadFromFile(const string& fileName);

    Base* operator[](int index) const;
    Keeper& operator+=(Base* obj);
    Keeper& operator=(const Keeper& other);
    friend ostream& operator<<(ostream& out, const Keeper& k);
};
