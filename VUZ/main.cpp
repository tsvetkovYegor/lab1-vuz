#include "Student.h"
#include "Teacher.h"
#include "Admin.h"
#include "VuzException.h"

// Временная проверка классов Student, Teacher, Admin (меню будет добавлено позже)
int main()
{
    try
    {
        string groups[] = { "1421", "1425" };
        string subjects[] = { "Программирование" };

        Base* s = new Student("Иванов Иван Иванович", "1421", "Прикладная информатика", 2, 4.5);
        Base* t = new Teacher("Смирнов Сергей Петрович", groups, 2, subjects, 1);
        Base* a = new Admin("Кузнецова Елена Андреевна", "Методист", "+7 812 000-00-00", "Расписание");

        cout << *s << endl << *t << endl << *a << endl;

        Base* t2 = t->clone();
        t2->edit();
        cout << *t2 << endl;

        delete s;
        delete t;
        delete a;
        delete t2;
    }
    catch (const VuzException& e)
    {
        cout << e.what() << endl;
    }
    return 0;
}
