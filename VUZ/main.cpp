#include "Keeper.h"
#include "Student.h"
#include "Teacher.h"
#include "Admin.h"
#include "VuzException.h"
#include "Input.h"

void printMenu()
{
    cout << endl << "========== ВУЗ ==========" << endl;
    cout << "1 - Добавить объект" << endl;
    cout << "2 - Удалить объект" << endl;
    cout << "3 - Вывести все объекты" << endl;
    cout << "4 - Вывести один объект" << endl;
    cout << "5 - Изменить объект" << endl;
    cout << "6 - Сохранить в файл" << endl;
    cout << "7 - Загрузить из файла" << endl;
    cout << "0 - Выход" << endl;
}

Base* createObject()
{
    cout << "1 - Студент" << endl;
    cout << "2 - Преподаватель" << endl;
    cout << "3 - Административный персонал" << endl;
    int type = readInt("Выберите тип: ");

    Base* obj;
    if (type == 1)
        obj = new Student();
    else if (type == 2)
        obj = new Teacher();
    else if (type == 3)
        obj = new Admin();
    else
        throw VuzException("Ошибка: нет такого типа");

    try
    {
        obj->input();
    }
    catch (...)
    {
        delete obj;
        throw;
    }
    return obj;
}

int main()
{
    Keeper keeper;
    int choice = -1;

    while (choice != 0)
    {
        printMenu();
        try
        {
            choice = readInt("Ваш выбор: ");
            switch (choice)
            {
            case 1:
                keeper += createObject();
                cout << "Объект добавлен" << endl;
                break;
            case 2:
                keeper.remove(readInt("Номер объекта: ") - 1);
                cout << "Объект удален" << endl;
                break;
            case 3:
                cout << keeper;
                break;
            case 4:
                cout << *keeper[readInt("Номер объекта: ") - 1];
                break;
            case 5:
                keeper[readInt("Номер объекта: ") - 1]->edit();
                cout << "Данные изменены" << endl;
                break;
            case 6:
                keeper.saveToFile(readLine("Имя файла: "));
                cout << "Данные сохранены" << endl;
                break;
            case 7:
                keeper.loadFromFile(readLine("Имя файла: "));
                cout << "Данные загружены" << endl;
                break;
            case 0:
                break;
            default:
                cout << "Нет такого пункта меню" << endl;
            }
        }
        catch (const VuzException& e)
        {
            cout << e.what() << endl;
            if (!cin)
                break;
        }
    }
    return 0;
}
