// ПРОГРАММА ДЛЯ ПОДСЧЕТА КОММУНАЛЬНЫХ УСЛУГ ЗА ЭЛЕКТРИЧЕСТВО
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

class IsCounterUpdated{};


int _getValidInput(string sout)
{
    const int maxValue = 100000000;
    int userInput;

    while (true)
    {
        cout << sout;

        if (cin >> userInput)
        {
            if (userInput < maxValue && userInput >= 0)
                return userInput;
            else
                cout << "Вы ввели нереалистичные показания счетчика. (Число отрицательное, вещественное или >= 100000000)" << endl;
        }
        else
        {
            cout << "Вы ввели не число." << endl;
            cin.clear(); // очистка флагов ввода
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очистка буфера ввода
        }
    }
}

int main()
{
    // цены за кВт/ч
    const double priceKWhDay = 3.4;
    const double priceKWhNoon = 2.2;
    // текущие показания счетчиков
    int kWhDay = 0; 
    int kWhNoon = 0;
    // новые показания счетчиков
    int newKWhDay = 0; 
    int newKWhNoon = 0;
    // собственно цена за улугу
    double price = 0;

    // прием новых показаний
    cout << "Здравствуйте. Я программа для помощи подсчета комунальных услуг за электричество.\n"
    << "Как только ваши показания перестанут отличаться от предыдуших, тогда я завершу работу." << endl;
    do
    {
        cout << "\nВведите ваш текущие показания за месяц.\n";
        newKWhDay = _getValidInput("День: ");
        newKWhNoon = _getValidInput("Ночь: ");
        
        // подсчет цены
        try 
        {
            if (!(newKWhDay >= kWhDay && newKWhNoon >= kWhNoon))
                throw IsCounterUpdated();
            price = (newKWhDay - kWhDay) * priceKWhDay + (newKWhNoon - kWhNoon) * priceKWhNoon;
        }
        catch (IsCounterUpdated e) // счетчики обнулились
        {
            cerr << "Ваш счетчик обнулился вам стоило нам об этом сообщить!" << endl;
            price = (newKWhDay - 0) * priceKWhDay + (newKWhNoon - 0) * priceKWhNoon;
        }

        kWhDay = newKWhDay;
        kWhNoon = newKWhNoon;

        cout << "Ваша цена за текущий месяц = " << fixed << setprecision(2) << price << endl;
    } while (price > 0);
}
