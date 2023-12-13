#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void CreateFile_Task1()
{
	try
	{
		ofstream out; // поток для записи
		out.open("hello.txt"); // открываем файл

		if (!out.is_open())
			throw runtime_error("Не удается открыть файл.");
			
		out << "Hello World!" << endl;

		out.close();
		cout << "File has been written." << endl;
	}
	catch (const exception& e)
	{
		cerr << "Ошибка: " << e.what() << endl;
	}
}

void ReadFile_Task2_4()
{
	try
	{
		string line;

		ifstream in("hello.txt");

		if (!in.is_open())
			throw runtime_error("Не удается открыть файл.");

		while (getline(in, line))
		{
			cout << line << endl;
		}

		in.close();
	}
	catch (const exception& e)
	{
		cerr << "Ошибка: " << e.what() << endl;
	}
}

void AddToFile_Task3()
{
	try {
		ofstream out("hello.txt", ios::app);

		if (!out.is_open())
			throw runtime_error("Не удается открыть файл.");

		// out.clear(); // если нужно очистить 

		string s;
		do {
			cin >> s;
			out << s << endl;
		} while (s.empty());

		out.close();
		cout << "Ввод закончен." << endl;
	}
	catch (const exception& e) {
		cerr << "Ошибка: " << e.what() << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "");
	ReadFile_Task2_4();

}