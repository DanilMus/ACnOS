#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void CreateFile_Task1()
{
	try
	{
		ofstream out; // ����� ��� ������
		out.open("hello.txt"); // ��������� ����

		if (!out.is_open())
			throw runtime_error("�� ������� ������� ����.");
			
		out << "Hello World!" << endl;

		out.close();
		cout << "File has been written." << endl;
	}
	catch (const exception& e)
	{
		cerr << "������: " << e.what() << endl;
	}
}

void ReadFile_Task2_4()
{
	try
	{
		string line;

		ifstream in("hello.txt");

		if (!in.is_open())
			throw runtime_error("�� ������� ������� ����.");

		while (getline(in, line))
		{
			cout << line << endl;
		}

		in.close();
	}
	catch (const exception& e)
	{
		cerr << "������: " << e.what() << endl;
	}
}

void AddToFile_Task3()
{
	try {
		ofstream out("hello.txt", ios::app);

		if (!out.is_open())
			throw runtime_error("�� ������� ������� ����.");

		// out.clear(); // ���� ����� �������� 

		string s;
		do {
			cin >> s;
			out << s << endl;
		} while (s.empty());

		out.close();
		cout << "���� ��������." << endl;
	}
	catch (const exception& e) {
		cerr << "������: " << e.what() << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "");
	ReadFile_Task2_4();

}