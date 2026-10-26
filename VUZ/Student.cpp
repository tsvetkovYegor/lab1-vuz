#include "Student.h"
#include "VuzException.h"
#include "Input.h"

Student::Student() : Base(), group("Не указана"), specialty("Не указана"),
                     course(1), avgScore(2)
{
    cout << "Student: вызван конструктор без параметров" << endl;
}

Student::Student(const string& fio, const string& group, const string& specialty,
                 int course, double avgScore) : Base(fio)
{
    cout << "Student: вызван конструктор с параметрами" << endl;
    setGroup(group);
    setSpecialty(specialty);
    setCourse(course);
    setAvgScore(avgScore);
}

Student::Student(const Student& other) : Base(other), group(other.group),
    specialty(other.specialty), course(other.course), avgScore(other.avgScore)
{
    cout << "Student: вызван конструктор копирования" << endl;
}

Student::~Student()
{
    cout << "Student: вызван деструктор" << endl;
}

string Student::getGroup() const { return group; }
string Student::getSpecialty() const { return specialty; }
int Student::getCourse() const { return course; }
double Student::getAvgScore() const { return avgScore; }

void Student::setGroup(const string& group)
{
    if (group.empty())
        throw VuzException("Ошибка: группа не может быть пустой");
    this->group = group;
}

void Student::setSpecialty(const string& specialty)
{
    if (specialty.empty())
        throw VuzException("Ошибка: специальность не может быть пустой");
    this->specialty = specialty;
}

void Student::setCourse(int course)
{
    if (course < 1 || course > 6)
        throw VuzException("Ошибка: курс должен быть от 1 до 6");
    this->course = course;
}

void Student::setAvgScore(double avgScore)
{
    if (avgScore < 2 || avgScore > 5)
        throw VuzException("Ошибка: средний балл должен быть от 2 до 5");
    this->avgScore = avgScore;
}

string Student::getType() const
{
    return "Студент";
}

Base* Student::clone() const
{
    return new Student(*this);
}

void Student::input()
{
    setFio(readLine("Введите ФИО: "));
    setGroup(readLine("Введите группу: "));
    setSpecialty(readLine("Введите специальность: "));
    setCourse(readInt("Введите курс: "));
    setAvgScore(readDouble("Введите средний балл: "));
}

void Student::edit()
{
    cout << "1 - ФИО" << endl;
    cout << "2 - Группа" << endl;
    cout << "3 - Специальность" << endl;
    cout << "4 - Курс" << endl;
    cout << "5 - Средний балл" << endl;
    int choice = readInt("Что изменить: ");
    switch (choice)
    {
    case 1: setFio(readLine("Новое ФИО: ")); break;
    case 2: setGroup(readLine("Новая группа: ")); break;
    case 3: setSpecialty(readLine("Новая специальность: ")); break;
    case 4: setCourse(readInt("Новый курс: ")); break;
    case 5: setAvgScore(readDouble("Новый средний балл: ")); break;
    default: throw VuzException("Ошибка: нет такого пункта");
    }
}

void Student::print(ostream& out) const
{
    out << "[" << getType() << "]" << endl;
    out << "ФИО: " << fio << endl;
    out << "Группа: " << group << endl;
    out << "Специальность: " << specialty << endl;
    out << "Курс: " << course << endl;
    out << "Средний балл: " << avgScore << endl;
}

void Student::save(ostream& out) const
{
    out << "STUDENT" << endl;
    out << fio << endl;
    out << group << endl;
    out << specialty << endl;
    out << course << endl;
    out << avgScore << endl;
}

void Student::load(istream& in)
{
    string s;
    getline(in, s); setFio(s);
    getline(in, s); setGroup(s);
    getline(in, s); setSpecialty(s);
    getline(in, s);
    try { setCourse(stoi(s)); }
    catch (const invalid_argument&) { throw VuzException("Ошибка: неверный курс в файле"); }
    getline(in, s);
    try { setAvgScore(stod(s)); }
    catch (const invalid_argument&) { throw VuzException("Ошибка: неверный средний балл в файле"); }
}

Student& Student::operator=(const Student& other)
{
    if (this != &other)
    {
        fio = other.fio;
        group = other.group;
        specialty = other.specialty;
        course = other.course;
        avgScore = other.avgScore;
    }
    return *this;
}
