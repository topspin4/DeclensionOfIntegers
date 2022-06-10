#include <QCoreApplication>

#include <iostream>
#include <ctime>

#include <DeclensionOfIntegers/declensionOfIntegers.h>

long long randomLL()
{
    srand(time(NULL));

    return (long long)(((double)rand()/(RAND_MAX)) * rand() * 100);
}

int randomG()
{
    srand(time(NULL));

    return rand() % 3;
}

int randomC()
{
    srand(time(NULL));

    return rand() % 6;
}

void getRandom()
{
    long long number = randomLL();
    string sGender = DeclensionOfIntegers::genders[randomG()];
    string sCase = DeclensionOfIntegers::cases[randomC()];

    cout << "ЗНАЧЕНИЕ: " << number << endl;
    cout << "ПОЛ: " << sGender << endl;
    cout << "ПАДЕЖ: " << sCase << endl;
    cout << "Результат: " << DeclensionOfIntegers::declInts(number, sGender, sCase) << endl;

    string cmd;
    cout << "Для продолжения введите любой символ. Для выхода нажмите\"q\" : ";
    cin >> cmd;

    if (cmd == "q")
    {
        exit(0);
    }
    else
    {
        getRandom();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    getRandom();
}
