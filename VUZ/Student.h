#pragma once
#include "Base.h"

class Student : public Base
{
private:
    string group;
    string specialty;
    int course;
    double avgScore;

public:
    Student();
    Student(const string& fio, const string& group, const string& specialty,
            int course, double avgScore);
    Student(const Student& other);
    ~Student();

    string getGroup() const;
    string getSpecialty() const;
    int getCourse() const;
    double getAvgScore() const;

    void setGroup(const string& group);
    void setSpecialty(const string& specialty);
    void setCourse(int course);
    void setAvgScore(double avgScore);

    string getType() const override;
    Base* clone() const override;
    void input() override;
    void edit() override;
    void print(ostream& out) const override;
    void save(ostream& out) const override;
    void load(istream& in) override;

    Student& operator=(const Student& other);
};
