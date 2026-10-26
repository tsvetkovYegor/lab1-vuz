#include "Student.h"
#include "VuzException.h"

// Временная проверка класса Student (меню будет добавлено позже)
int main()
{
    try
    {
        Student* s1 = new Student("Иванов Иван Иванович", "1421", "Прикладная информатика", 2, 4.5);
        cout << *s1 << endl;

        Student* s2 = new Student(*s1);
        cout << *s2 << endl;

        Student* s3 = new Student();
        s3->input();
        cout << *s3 << endl;

        delete s1;
        delete s2;
        delete s3;
    }
    catch (const VuzException& e)
    {
        cout << e.what() << endl;
    }
    return 0;
}
