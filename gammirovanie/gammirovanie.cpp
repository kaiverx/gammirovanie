#include <iostream>
#include <string>

using namespace std;

int decimalToBinary(int k) 
{
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
int binaryToDecimal(int binary)
{
	int decimal = 0;
	int power = 1; // Начинаем с 2^0

	while (binary > 0) {
		// Извлекаем младший бит (0 или 1)
		int lastDigit = binary % 10;
		// Добавляем соответствующую степень двойки к результату
		decimal += lastDigit * power;
		// Переходим к следующей степени двойки
		power *= 2;
		// Удаляем младший бит
		binary /= 10;
	}

	return decimal;
}

int addBinary(int a, int b) 
{
	int result = 0; // Результат сложения
	int carry = 0;  // Перенос
	int power = 1;  // Текущая степень двойки

	while (a > 0 || b > 0 || carry > 0) {
		// Извлекаем младшие разряды
		int bitA = a % 10;
		int bitB = b % 10;

		// Считаем сумму и перенос
		int sum = bitA + bitB + carry;
		carry = sum / 2;
		sum = sum % 2;

		// Формируем результат
		result += sum * power;

		// Переходим к следующему разряду
		power *= 10;
		a /= 10;
		b /= 10;
	}

	return result;
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
	for (int i = 0; i < n-1; i++)
	{
		ascii[i] = static_cast<int>(shifr[i]);
		//cout << "ASCII i " << i << ": " << ascii[i] <<endl;
		int binary = decimalToBinary(ascii[i]);
		//кодирование при помощи ключа
		int decimal = addBinary(binary, key);
		//перевод из двоичной в десятичную
		int ASCII = binaryToDecimal(decimal);
		//проверка на выхождение за пределы аски кода
		if (ASCII == 256)
			ascii[i] = 0;
		else if (ASCII > 256)
		{
			int ASCII_change = ASCII;
			int k = 0;
			while (ASCII_change > 255)
			{
				ASCII_change -= 255;
				k++;
			}
			ascii[i] = ASCII - 255 * k;
		}
		else
			ascii[i] = ASCII;
		//cout << "ASCII i " << i << ": " << ascii[i]<<endl;
	
	}

	//преобразование из ascii в char
	for (int i = 0; i < n-1; i++)
	{
		shifr[i] = static_cast<char>(ascii[i]);
		cout << i << " " << shifr[i]<<endl;
	}

	delete[] shifr;
}