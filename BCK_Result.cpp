#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <vector>
#include <limits>

using namespace std;
class Code {
private:
    int digit;
    string letters;
public:
    Code(int digit, string letters) {
        this->digit = digit;
        this->letters = letters;
    }
    Code() {
        digit = 0;
        letters = "";
    }
    int getDigit() { return digit; }
    string getLetters() { return letters; }

    void print() {
        cout << "Digit: " << digit << ", letters: " << letters << endl;
    }

    bool isCorrect(int digit) {
        return this->digit == digit ? true : false;
    }
    bool isCorrect(string letters) {
        return this->letters == letters ? true : false;
    }
};

void rememberLetters(Code* codes);
void rememberDigits(Code* codes);
void practiceLetters(Code* codes);
void practiceDigits(Code* codes);

void toUpperCase(string& str);
bool isInDigits(int* arr, int size, int digit);
void deleteDigit(int* arr, int& size, int digit);


int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Code codes[10];
    codes[0] = Code(0, "НМ");
    codes[1] = Code(1, "ГЖ");
    codes[2] = Code(2, "ДТ");
    codes[3] = Code(3, "КХ");
    codes[4] = Code(4, "ЧЩ");
    codes[5] = Code(5, "ПБ");
    codes[6] = Code(6, "ШЛ");
    codes[7] = Code(7, "СЗ");
    codes[8] = Code(8, "ВФ");
    codes[9] = Code(9, "РЦ");

    int choise{ 77 };
    srand(time(NULL));
    do
    {
        cout << "Меню:\n" 
             << "1. Повторить буквы\n" 
             << "2. Повторить цифры\n" 
             << "3. Упражнение: буквы\n" 
             << "4. Упражнение: цифры\n"
             << "0. Выход\n";

        cout << ">> "; cin >> choise; cout << endl;
        switch (choise)
        {
        case 1: {
            rememberLetters(codes);
            break;
        }
        case 2: {
            rememberDigits(codes);
            break;
        }
        case 3: {
            practiceLetters(codes);
            break;
        }
        case 4: {
            practiceDigits(codes);
            break;
        }
        case 0: {
            cout << "Выход\n\n";
            break;
        }
        default:
            cout << "Некорректный ввод\n\n";
            break;
        }
    } while (choise);

    return 0;
}

void rememberLetters(Code* codes) {
    string tempLetters;
    int arr[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int size = 10;
    while (size) {
        int tempNumber = rand() % 10;

        if (!isInDigits(arr, size, tempNumber)) continue;
        
        deleteDigit(arr, size, tempNumber);

        try
        {
            cout << "Введите буквы для числа " << tempNumber << ": ";
            cin >> tempLetters;
            string trash;
            getline(cin, trash);
            
        }
        catch (const std::istream::failure& ex) {
            std::cerr << "Ошибка чтения символов: " << ex.what() << "\n";
            continue;
        }
        toUpperCase(tempLetters);

        while (!codes[tempNumber].isCorrect(tempLetters)) {
            cout << "Неправильно, попробуйте еще раз\n";
            cout << "Введите буквы для числа " << codes[tempNumber].getDigit() << ": ";
            cin >> tempLetters;
            string trash;
            getline(cin, trash);
        }
        cout << "Верно!\n";
    }
    cout << "Упражнение завершено\n---\n\n";
}



void rememberDigits(Code* codes) {
    int arr[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int size = 10;

    while (size) {
        int tempNumber = rand() % 10;
        int inputNumber{};

        if (!isInDigits(arr, size, tempNumber)) continue;

        deleteDigit(arr, size, tempNumber);
        cout << "Введите цифры для букв " << codes[tempNumber].getLetters() << ": ";
        cin >> inputNumber;

        while (!codes[tempNumber].isCorrect(inputNumber)) {
            cout << "Неправильно, попробуйте еще раз\n";
            cout << "Введите цифры для букв " << codes[tempNumber].getLetters() << ": ";
            cin >> inputNumber;
        }
        cout << "Верно!\n";
    }
    cout << "Упражнение завершено\n---\n\n";
}

void practiceLetters(Code* codes) {
    string tempLetters;
    int count{};
    vector<int> arr;

    cout << "Введите кол-во чисел: ";
    cin >> count; cout << endl;

    while (count) {
        int randNumber = 10 + rand() % 90;
        int randNumberFirstDig = randNumber % 10;
        int randNumberSecDig = randNumber / 10;

        if (std::find(arr.begin(), arr.end(), randNumber) != arr.end()) continue;
  
        arr.push_back(randNumber);

        cout << "Введите буквы для числа " << randNumber << ": ";
        cin >> tempLetters;
        toUpperCase(tempLetters);

        while (!codes[randNumberFirstDig].isCorrect(tempLetters.substr(2, 2)) || !codes[randNumberSecDig].isCorrect(tempLetters.substr(0, 2))) {
            cout << "Неправильно, попробуйте еще раз\n";
            cout << "Введите буквы для числа " << randNumber << ": ";
            cin >> tempLetters;
            toUpperCase(tempLetters);
        }
        cout << "Верно!\n";
        count--;
    }
    cout << "Упражнение завершено\n---\n\n";
}

void practiceDigits(Code* codes) {
    string tempLetters;
    int count{};
    vector<int> arr;

    cout << "Введите кол-во чисел: ";
    cin >> count; cout << endl;

    while (count) {

        int randNumber = 10 + rand() % 90;
        int randNumberFirstDig = randNumber % 10;
        int randNumberSecDig = randNumber / 10;

        int inputNumber{};
        if (std::find(arr.begin(), arr.end(), randNumber) != arr.end()) continue;
        arr.push_back(randNumber);

        string randLetters = codes[randNumberSecDig].getLetters() + codes[randNumberFirstDig].getLetters();
        cout << "Введите цифры для букв " << randLetters << ": ";
        cin >> inputNumber;

        while (!codes[randNumberFirstDig].isCorrect(randNumberFirstDig) || !codes[randNumberSecDig].isCorrect(randNumberSecDig)) {
            cout << "Неправильно, попробуйте еще раз\n";
            cout << "Введите цифры для числа " << randLetters << ": ";
            cin >> inputNumber;
        }
        cout << "Верно!\n";
        count--;
    }
    cout << "Упражнение завершено\n---\n\n";
}

void toUpperCase(string& str) {
    for (char& c : str) {
        if ('а' < c && c < 'я')
            c -= 32;
    }
}

bool isInDigits(int* arr, int size, int digit) {
    for (int i{}; i < size; ++i) {
        if (arr[i] == digit)  return true; 
    }
    return false;
}

void deleteDigit(int* arr, int& size, int digit) {
    int step{};
    for (int i{}; i < size; i++){
        if (arr[i] == digit) {
            step++;
            continue;
        }
        arr[i - step] = arr[i];
    }
    size--;
};