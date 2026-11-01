#pragma once
#include "Base.h"

class Teacher : public Base
{
private:
    string* groups;       // динамический массив групп
    int groupCount;
    string* subjects;     // динамический массив предметов
    int subjectCount;

    // вспомогательные функции для работы с массивами строк
    static string* copyArray(const string* arr, int count);
    static void addToArray(string*& arr, int& count, const string& value);
    static void removeFromArray(string*& arr, int& count, int index);

public:
    Teacher();
    Teacher(const string& fio, const string* groups, int groupCount,
            const string* subjects, int subjectCount);
    Teacher(const Teacher& other);
    ~Teacher();

    int getGroupCount() const;
    int getSubjectCount() const;
    string getGroup(int index) const;
    string getSubject(int index) const;

    void setGroup(int index, const string& group);
    void setSubject(int index, const string& subject);
    void addGroup(const string& group);
    void addSubject(const string& subject);
    void removeGroup(int index);
    void removeSubject(int index);

    string getType() const override;
    Base* clone() const override;
    void input() override;
    void edit() override;
    void print(ostream& out) const override;
    void save(ostream& out) const override;
    void load(istream& in) override;

    Teacher& operator=(const Teacher& other);
};
