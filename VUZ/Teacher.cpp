#include "Teacher.h"
#include "VuzException.h"
#include "Input.h"

string* Teacher::copyArray(const string* arr, int count)
{
    if (count == 0)
        return nullptr;
    string* result = new string[count];
    for (int i = 0; i < count; i++)
        result[i] = arr[i];
    return result;
}

void Teacher::addToArray(string*& arr, int& count, const string& value)
{
    string* result = new string[count + 1];
    for (int i = 0; i < count; i++)
        result[i] = arr[i];
    result[count] = value;
    delete[] arr;
    arr = result;
    count++;
}

void Teacher::removeFromArray(string*& arr, int& count, int index)
{
    if (index < 0 || index >= count)
        throw VuzException("Ошибка: элемента с таким номером нет");
    string* result = nullptr;
    if (count > 1)
    {
        result = new string[count - 1];
        int j = 0;
        for (int i = 0; i < count; i++)
            if (i != index)
                result[j++] = arr[i];
    }
    delete[] arr;
    arr = result;
    count--;
}

Teacher::Teacher() : Base(), groups(nullptr), groupCount(0),
                     subjects(nullptr), subjectCount(0)
{
    cout << "Teacher: вызван конструктор без параметров" << endl;
}

Teacher::Teacher(const string& fio, const string* groups, int groupCount,
                 const string* subjects, int subjectCount) : Base(fio)
{
    cout << "Teacher: вызван конструктор с параметрами" << endl;
    if (groupCount < 0 || subjectCount < 0)
        throw VuzException("Ошибка: количество не может быть отрицательным");
    this->groups = copyArray(groups, groupCount);
    this->groupCount = groupCount;
    this->subjects = copyArray(subjects, subjectCount);
    this->subjectCount = subjectCount;
}

Teacher::Teacher(const Teacher& other) : Base(other)
{
    cout << "Teacher: вызван конструктор копирования" << endl;
    groups = copyArray(other.groups, other.groupCount);
    groupCount = other.groupCount;
    subjects = copyArray(other.subjects, other.subjectCount);
    subjectCount = other.subjectCount;
}

Teacher::~Teacher()
{
    cout << "Teacher: вызван деструктор" << endl;
    delete[] groups;
    delete[] subjects;
}

int Teacher::getGroupCount() const { return groupCount; }
int Teacher::getSubjectCount() const { return subjectCount; }

string Teacher::getGroup(int index) const
{
    if (index < 0 || index >= groupCount)
        throw VuzException("Ошибка: группы с таким номером нет");
    return groups[index];
}

string Teacher::getSubject(int index) const
{
    if (index < 0 || index >= subjectCount)
        throw VuzException("Ошибка: предмета с таким номером нет");
    return subjects[index];
}

void Teacher::setGroup(int index, const string& group)
{
    if (index < 0 || index >= groupCount)
        throw VuzException("Ошибка: группы с таким номером нет");
    if (group.empty())
        throw VuzException("Ошибка: группа не может быть пустой");
    groups[index] = group;
}

void Teacher::setSubject(int index, const string& subject)
{
    if (index < 0 || index >= subjectCount)
        throw VuzException("Ошибка: предмета с таким номером нет");
    if (subject.empty())
        throw VuzException("Ошибка: предмет не может быть пустым");
    subjects[index] = subject;
}

void Teacher::addGroup(const string& group)
{
    if (group.empty())
        throw VuzException("Ошибка: группа не может быть пустой");
    addToArray(groups, groupCount, group);
}

void Teacher::addSubject(const string& subject)
{
    if (subject.empty())
        throw VuzException("Ошибка: предмет не может быть пустым");
    addToArray(subjects, subjectCount, subject);
}

void Teacher::removeGroup(int index)
{
    removeFromArray(groups, groupCount, index);
}

void Teacher::removeSubject(int index)
{
    removeFromArray(subjects, subjectCount, index);
}

string Teacher::getType() const
{
    return "Преподаватель";
}

Base* Teacher::clone() const
{
    return new Teacher(*this);
}

void Teacher::input()
{
    setFio(readLine("Введите ФИО: "));

    delete[] groups;
    groups = nullptr;
    groupCount = 0;
    int n = readInt("Сколько групп ведет: ");
    if (n < 0)
        throw VuzException("Ошибка: количество не может быть отрицательным");
    for (int i = 0; i < n; i++)
        addGroup(readLine("Группа " + to_string(i + 1) + ": "));

    delete[] subjects;
    subjects = nullptr;
    subjectCount = 0;
    n = readInt("Сколько предметов преподает: ");
    if (n < 0)
        throw VuzException("Ошибка: количество не может быть отрицательным");
    for (int i = 0; i < n; i++)
        addSubject(readLine("Предмет " + to_string(i + 1) + ": "));
}

void Teacher::edit()
{
    cout << "1 - ФИО" << endl;
    cout << "2 - Добавить группу" << endl;
    cout << "3 - Изменить группу" << endl;
    cout << "4 - Удалить группу" << endl;
    cout << "5 - Добавить предмет" << endl;
    cout << "6 - Изменить предмет" << endl;
    cout << "7 - Удалить предмет" << endl;
    int choice = readInt("Что изменить: ");
    int index;
    switch (choice)
    {
    case 1:
        setFio(readLine("Новое ФИО: "));
        break;
    case 2:
        addGroup(readLine("Новая группа: "));
        break;
    case 3:
        index = readInt("Номер группы: ") - 1;
        setGroup(index, readLine("Новое значение: "));
        break;
    case 4:
        removeGroup(readInt("Номер группы: ") - 1);
        break;
    case 5:
        addSubject(readLine("Новый предмет: "));
        break;
    case 6:
        index = readInt("Номер предмета: ") - 1;
        setSubject(index, readLine("Новое значение: "));
        break;
    case 7:
        removeSubject(readInt("Номер предмета: ") - 1);
        break;
    default:
        throw VuzException("Ошибка: нет такого пункта");
    }
}

void Teacher::print(ostream& out) const
{
    out << "[" << getType() << "]" << endl;
    out << "ФИО: " << fio << endl;
    out << "Группы: ";
    if (groupCount == 0)
        out << "нет";
    for (int i = 0; i < groupCount; i++)
        out << i + 1 << ") " << groups[i] << "  ";
    out << endl;
    out << "Предметы: ";
    if (subjectCount == 0)
        out << "нет";
    for (int i = 0; i < subjectCount; i++)
        out << i + 1 << ") " << subjects[i] << "  ";
    out << endl;
}

void Teacher::save(ostream& out) const
{
    out << "TEACHER" << endl;
    out << fio << endl;
    out << groupCount << endl;
    for (int i = 0; i < groupCount; i++)
        out << groups[i] << endl;
    out << subjectCount << endl;
    for (int i = 0; i < subjectCount; i++)
        out << subjects[i] << endl;
}

void Teacher::load(istream& in)
{
    string s;
    int n;
    getline(in, s);
    setFio(s);

    delete[] groups;
    groups = nullptr;
    groupCount = 0;
    getline(in, s);
    try { n = stoi(s); }
    catch (const invalid_argument&) { throw VuzException("Ошибка: неверное количество групп в файле"); }
    for (int i = 0; i < n; i++)
    {
        getline(in, s);
        addGroup(s);
    }

    delete[] subjects;
    subjects = nullptr;
    subjectCount = 0;
    getline(in, s);
    try { n = stoi(s); }
    catch (const invalid_argument&) { throw VuzException("Ошибка: неверное количество предметов в файле"); }
    for (int i = 0; i < n; i++)
    {
        getline(in, s);
        addSubject(s);
    }
}

Teacher& Teacher::operator=(const Teacher& other)
{
    if (this != &other)
    {
        fio = other.fio;
        delete[] groups;
        delete[] subjects;
        groups = copyArray(other.groups, other.groupCount);
        groupCount = other.groupCount;
        subjects = copyArray(other.subjects, other.subjectCount);
        subjectCount = other.subjectCount;
    }
    return *this;
}
