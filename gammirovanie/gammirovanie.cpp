#include <iostream>
#include <string>
#include <cstdlib>

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

    cout << "ГАММИРОВАНИЕ" << endl;

    string stroka;
    int key = 0;
    int* ascii = nullptr;
    char* shifr = nullptr;
    int n = 0;

    for (;;)
    {
        cout << "1. Введите '1' для введения текста и ключа" << endl;
        cout << "2. Введите '2' для шифрования текста" << endl;
        cout << "3. Введите '3' для вывода зашифрованного текста" << endl;
        cout << "4. Введите '0' для завершения работы программы" << endl;
        cout << "Выберите нужный вам пункт и введите нужное значение с клавиатуры: ";
        int menu;
        cin >> menu;
        cout << endl;
        cin.ignore(); // Игнорируем символ новой строки после ввода пункта меню
        if (menu == 0)
        {
            delete[] ascii;
            delete[] shifr;
            break;
        }

        switch (menu)
        {
        case(1):
            cout << "Введите текст: ";
            getline(cin, stroka);

            n = stroka.length() + 1;

            // Освобождаем память, если она уже была выделена
            if (ascii != nullptr) {
                delete[] ascii;
                delete[] shifr;
            }

            // Создаем массивы
            ascii = new int[n];
            shifr = new char[n];

            // Копируем строку в массив shifr
            strcpy_s(shifr, n, stroka.c_str());
            cout << "Введенная строка: " << shifr << endl;

            // Создаем ключ
            cout << "Введите двоичный ключ для шифрования текста: ";
            cin >> key;
            cin.ignore(); // Игнорируем символ новой строки после ввода ключа
            cout << endl;
            break;

        case(2):
            if (ascii == nullptr || shifr == nullptr) {
                cout << "Сначала введите текст и ключ (пункт 1)." << endl;
                break;
            }

            // Преобразование из char в ASCII и шифрование
            for (int i = 0; i < n - 1; i++)
            {
                ascii[i] = static_cast<int>(shifr[i]);
                int binary = decimalToBinary(ascii[i]);
                // Кодирование при помощи ключа
                int encodedBinary = addBinary(binary, key);
                // Перевод из двоичной в десятичную
                int ASCII = binaryToDecimal(encodedBinary);
                // Проверка на выхождение за пределы ASCII кода
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
            }
            break;

        case(3):
            if (ascii == nullptr) {
                cout << "Сначала введите текст и ключ (пункт 1)." << endl;
                break;
            }

            // Преобразование из ASCII в char и вывод
            cout << "Зашифрованный текст: ";
            for (int i = 0; i < n - 1; i++)
            {
                shifr[i] = static_cast<char>(ascii[i]);
                cout << shifr[i];
            }
            cout << endl;
            break;

        default:
            cout << "Неверный пункт меню!!! Введите значение, которое указано в нужном вам пункте, либо введите '0' для завершения работы программы." << endl;
            break;
        }
    }
}
