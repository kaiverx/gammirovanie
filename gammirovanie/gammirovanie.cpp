#include <iostream>
#include <string>

using namespace std;

int decimalToBinaryInt(int k) {
	int binaryNum = 0;
	int place = 1; // Текущий разряд двоичного числа

	while (k > 0) {
		int lastBit = k % 2;
		binaryNum += lastBit * place;
		k /= 2;
		place *= 10; // Переходим на следующий разряд в "десятичном представлении" двоичного числа
	}

	return binaryNum;
}

int main()
{
	setlocale(LC_ALL, "russian");

	cout << "Гаммирование" << endl;

	int number;

	//создание строки
	string stroka;
	getline(cin, stroka);
	//размер созданной строки +1 для корректной работы со строками
	int n=stroka.length()+1;

	//массив хранящий коды ascii
	int* ascii = new int[n];
	//массив хранящий буквы и символы
	char* shifr = new char[n];

	//копирование строки в массив shifr
	strcpy_s(shifr, n, stroka.c_str());
	cout << "Введенная строка: " << shifr << endl;

	//создание ключа
	int key;
	cout << "Введите ключ для шифрования текста: ";
	cin >> key;
	cout << endl;

	//преобразование из char в ascii
	for (int i = 0; i < n; i++)
	{
		ascii[i] = static_cast<int>(shifr[i]);
		//cout << "ASCII i " << i << ": " << ascii[i] << " -> ";
		int binary = decimalToBinaryInt(ascii[i]);
		//cout << "Binary: " << binary << endl;
		ascii[i] = binary;
		//cout << "ASCII i " << i << ": " << ascii[i]<<endl;

	}

	/*
	//проверка правильности перевода
	for (int i = 0; i < n; i++)
	{
		cout << "i " << i <<" " << ascii[i] << endl;
	}*/

	//преобразование из ascii в char
	for (int i = 0; i < n; i++)
	{
		shifr[i] = static_cast<char>(ascii[i]);
	}

	/*
	//проверка правильности перевода
	for (int i = 0; i < n; i++)
	{
		cout << "i " << i << " " << shifr[i] << endl;
	}*/

	delete[] shifr;
}