// РАБОТА С ИСКЛЮЧЕНИЯМИ
#include <iostream>
#include <excpt.h>
#include <limits>
#include <cmath>
#include <vector>

using namespace std;

// целочисленная арифметика
void integer_arithmentic()
{
	try
	{
		short result = 32767;
		if (result == numeric_limits<short>::max())
			throw exception("Сложение с максимальным числом.");
		result += 1;
	}
	catch (const exception& e)
	{
		cerr << "Переполнение целого числа: " << e.what() << endl;
	}

	try
	{
		int denomitator = 0;
		if (denomitator == 0)
			throw exception("Деление на ноль.");
		int result = 42 / denomitator; 
	}
	catch (const exception& e)
	{
		cerr << "Деление целого числа на ноль: " << e.what() << endl;
	}
}

void integer_arithmentic_SEH()
{
	__try
	{
		short result = 32767;
		if (result == numeric_limits<short>::max())
			throw exception("Сложение с максимальным числом.");
		result += 1;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		cerr << "Переполнение целого числа." << endl;
	}

	__try
	{
		int denomitator = 0;
		int result = 42 / denomitator;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		cerr << "Деление целого числа на ноль." << endl;
	}
}

// работа с плавающей точкой
void double_arithmetic()
{
	try
	{
		int a = -1;
		if (a < 0)
			throw exception("Вычисление корня из отрицательного числа");
		double result = sqrt(-1);
	}
	catch (const exception& e)
	{
		cerr << "Ошибка при вычислении корня: " << e.what() << endl;
	}

	try
	{
		int denomitator = 0.0;
		if (denomitator == 0.0)
			throw exception("Деление на ноль.");
		int result = 42.0 / denomitator; 
	}
	catch (const exception& e)
	{
		cerr << "Деление вещественного числа на ноль: " << e.what() << endl;
	}
}

void double_arithmetic_SEH()
{
	__try
	{
		int a = -1;
		if (a < 0)
			throw exception("Вычисление корня из отрицательного числа");
		double result = sqrt(-1);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		cerr << "Ошибка при вычислении корня." << endl;
	}

	__try
	{
		int denomitator = 0.0;
		if (denomitator == 0.0)
			throw exception("Деление на ноль.");
		int result = 42.0 / denomitator;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		cerr << "Деление вещественного числа на ноль."<< endl;
	}
}

// работа с динамикой
void work_with_dinamic()
{
	try
	{
		int* ptr = nullptr;
		if (ptr == nullptr)
			throw exception("Пустая ссылка.");
		int value = *ptr;
	}
	catch (const exception& e)
	{
		cerr << "Ошибка при обращении к пустому указателю: " << e.what() << endl;
	}

	try
	{
		vector<int> v;
		int value2 = v.at(15);
	}
	catch (const out_of_range& e)
	{
		cerr << "Обращение за пределы массива: " << e.what() << endl;
	}


	//vector<int> vec;
	//try {
	//	while (true) {
	//		vec.push_back(1);
	//	}
	//}
	//catch (const std::bad_alloc& e) {
	//	std::cout << "Место закончилось после вставки " << vec.size() << " элементов" << std::endl;
	//}
}

void work_with_dinamic_SEH()
{
	__try
	{
		int* ptr = nullptr;
		int value = *ptr;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		cerr << "Ошибка при обращении к пустому указателю." << endl;
	}

	/*__try
	{
		vector<int> v;
		int value2 = v[15];
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		cerr << "Обращение за пределы динамического массива." << endl;
	}*/
}


int main()
{
	setlocale(LC_ALL, "");

	integer_arithmentic();
	double_arithmetic();
	work_with_dinamic();

	integer_arithmentic_SEH();
	double_arithmetic_SEH();
	work_with_dinamic_SEH();
}