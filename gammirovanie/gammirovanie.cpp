#include <iostream>
#include <string>
#include <cstdlib>
#include <locale>
#include <stdexcept> // Для обработки исключений

using namespace std;

bool isBinary(int key) {
    while (key > 0) {
        int digit = key % 10;
        if (digit != 0 && digit != 1) {
            return false;
        }
        key /= 10;
    }
    return true;
}

bool isNumber(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// перевод из десятичной в двоичную
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

// перевод из двоичной в десятичную
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

// сложение с ключом
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

// вычитание с ключом
int subtractBinary(int a, int b) {
    int result = 0; // Результат вычитания
    int borrow = 0; // Заимствование
    int power = 1;  // Текущая степень десяти

    while (a > 0 || b > 0 || borrow != 0) {
        // Извлекаем младшие разряды
        int bitA = a % 10;
        int bitB = b % 10;

        // Вычитаем и учитываем заимствование
        int sub = bitA - bitB - borrow;

        if (sub < 0) {
            sub += 2; // Добавляем 2, если не хватает
            borrow = 1; // Устанавливаем заимствование
        }
        else {
            borrow = 0; // Сбрасываем заимствование
        }

        // Формируем результат
        result += sub * power;

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
    int check_punkt = 0;

    for (;;) {
        cout << "1. Введите '1' для введения текста и ключа" << endl;
        cout << "2. Введите '2' для шифрования текста" << endl;
        cout << "3. Введите '3' для вывода зашифрованного текста" << endl;
        cout << "4. Введите '4' для декодирования текста при помощи ключа" << endl;
        cout << "5. Введите '5' для вывода дешифрованного текста" << endl;
        cout << "6. Введите '0' для завершения работы программы" << endl;
        cout << "Выберите нужный вам пункт и введите нужное значение с клавиатуры: ";

        string menuStr;
        cin >> menuStr;
        cout << endl;
        cin.ignore(); // Игнорируем символ новой строки после ввода пункта меню

        // Проверка корректности ввода меню
        if (!isNumber(menuStr)) {
            cout << "Ошибка: Пункт меню должен быть числовым значением." << endl;
            continue;
        }

        int menu = stoi(menuStr);

        if (menu < 0 || menu > 6) {
            cout << "Ошибка: Неверный пункт меню." << endl;
            continue;
        }

        if (menu == 0) {
            delete[] ascii;
            delete[] shifr;
            break;
        }

        switch (menu)
        {
        case(1): {
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

            // Ввод и проверка ключа
            while (true) {
                string keyStr;
                cout << "Введите двоичный ключ для шифрования текста: ";
                cin >> keyStr;
                cin.ignore(); // Игнорируем символ новой строки после ввода ключа

                // Проверка корректности ввода
                if (isNumber(keyStr)) {
                    try {
                        key = stoi(keyStr);
                        if (isBinary(key)) {
                            cout << "Ключ принят." << endl;
                            check_punkt = 1;
                            break; // Выходим из цикла ввода ключа
                        }
                        else {
                            cout << "Ошибка: Ключ должен быть двоичным числом." << endl;
                        }
                    }
                    catch (invalid_argument&) {
                        cout << "Ошибка: Неверный формат ключа." << endl;
                    }
                    catch (out_of_range&) {
                        cout << "Ошибка: Ключ слишком длинный." << endl;
                    }
                }
                else {
                    cout << "Ошибка: Ключ должен быть числовым значением." << endl;
                }
            }
            cout << endl;
            break;
        }
        case(2): {
            if (check_punkt == 0)
            {
                cout << "Невозможно выполнить. Сначала выполните ввод текста и ключа (пункт 1)." << endl;
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
            cout << "Текст зашифрован и сохранен" << endl;
            check_punkt = 2;
            break;
        }
        case(3): {
            if (check_punkt == 0)
            {
                cout << "Невозможно выполнить. Сначала выполните ввод текста и ключа (пункт 1), а так же выполните шифрование текста (пункт 2)." << endl;
                break;
            }
            else if (check_punkt == 1)
            {
                cout << "Невозможно выполнить. Сначала выполните шифрование текста (пункт 2)." << endl;
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
        }
        case(4): {
            if (check_punkt == 0)
            {
                cout << "Невозможно выполнить. Сначала выполните ввод текста и ключа (пункт 1), а так же выполните шифрование текста (пункт 2)." << endl;
                break;
            }
            else if (check_punkt == 1)
            {
                cout << "Невозможно выполнить. Сначала выполните шифрование текста (пункт 2)." << endl;
                break;
            }
            // Преобразование из char в ASCII и дешифрование
            for (int i = 0; i < n - 1; i++)
            {
                ascii[i] = static_cast<int>(shifr[i]);
                int check_key = binaryToDecimal(key);
                while (ascii[i] < check_key)
                    ascii[i] += 256;
                int binary = decimalToBinary(ascii[i]);
                // Декодирование при помощи ключа
                int decodedBinary = subtractBinary(binary, key);
                // Перевод из двоичной в десятичную
                int ASCII = binaryToDecimal(decodedBinary);
                // Проверка на выхождение за пределы ASCII кода
                if (ASCII < 0)
                    ascii[i] = 0;
                else if (ASCII > 255)
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

                // Запись дешифрованного символа в массив
                shifr[i] = static_cast<char>(ascii[i]);
            }
            cout << "Текст дешифрован и сохранен" << endl;
            check_punkt = 3;
            break;
        }
        case(5): {
            if (check_punkt == 0)
            {
                cout << "Невозможно выполнить. Сначала выполните ввод текста и ключа (пункт 1), а так же выполните шифрование текста (пункт 2) и дешифровку текста (пункт 4)." << endl;
                break;
            }
            else if (check_punkt == 1)
            {
                cout << "Невозможно выполнить. Сначала выполните шифрование текста (пункт 2) и дешифровку текста (пункт 4)." << endl;
                break;
            }
            else if (check_punkt == 2)
            {
                cout << "Невозможно выполнить. Сначала выполните дешифровку текста (пункт 4)." << endl;
                break;
            }

            // Преобразование из ASCII в char и вывод
            cout << "Дешифрованный текст: ";
            for (int i = 0; i < n - 1; i++)
            {
                cout << shifr[i];
            }
            cout << endl;
            check_punkt = 0;
            break;
        }
        default:
            cout << "Неверный пункт меню!!! Введите значение, которое указано в нужном вам пункте, либо введите '0' для завершения работы программы." << endl;
            break;
        }
    }
}
