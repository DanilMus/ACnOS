// ПРОГРАММА ДЛЯ ПОДСЧЕТА КОММУНАЛЬНЫХ УСЛУГ ЗА ЭЛЕКТРИЧЕСТВО
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    // цены за кВт/ч
    const double priceKWhDay = 3.4;
    const double priceKWhNoon = 2.2;
    // текущие показания счетчиков
    unsigned int kWhDay = 0; 
    unsigned int kWhNoon = 0;
    // новые показания счетчиков
    unsigned int newKWhDay = 0; 
    unsigned int newKWhNoon = 0;
    // собственно цена за улугу
    double price = 0;

    // прием новых показаний
    cout << "Здравствуйте. Я программа для помощи подсчета комунальных услуг за электричество.\n" 
    << "Введите ваш текущие показания за месяц.\n"
    << "День: ";
    cin >> kWhDay;
    cout << "Ночь: ";
    cin >> kWhNoon;
    
    // подсчет цены
    if (newKWhDay >= kWhDay && newKWhNoon >= kWhNoon)
        price = (newKWhDay - kWhDay) * priceKWhDay + (newKWhNoon - kWhNoon) * priceKWhNoon;
    else // счетчики обнулились
        price = (newKWhDay - 0) * priceKWhDay + (newKWhNoon - 0) * priceKWhNoon;
    kWhDay = newKWhDay;
    kWhNoon = newKWhNoon;

    cout << "Ваша цена за текущий месяц = " << fixed << setprecision(2) << price;
}