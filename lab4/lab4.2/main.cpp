#include <iostream>
#include <sstream>
#include <string>
#include "Time.h"

// Функция безопасного ввода целого числа
int inputInt(const std::string& prompt) {
    using namespace std;
    string input;
    int value;
    
    while (true) {
        cout << prompt;
        getline(cin, input);
        
        if (input.empty()) {
            cout << "Ошибка: пустой ввод. Пожалуйста, введите целое число." << endl;
            continue;
        }
        
        stringstream ss(input);
        
        if (ss >> value) {
            string remaining;
            if (ss >> remaining) {
                cout << "Ошибка: введены лишние символы: '" << remaining << "'" << endl;
            } else {
                return value;
            }
        } else {
            cout << "Ошибка: '" << input << "' не является целым числом." << endl;
        }
    }
}

// Функция для ввода времени с клавиатуры
Time inputTime(const std::string& prompt) {
    using namespace std;
    
    cout << "\n" << prompt << endl;
    
    int h, m;
    
    while (true) {
        h = inputInt("Часы (0-23): ");
        if (h >= 0 && h <= 23) break;
        cout << "Ошибка: часы должны быть от 0 до 23" << endl;
    }
    
    while (true) {
        m = inputInt("Минуты (0-59): ");
        if (m >= 0 && m <= 59) break;
        cout << "Ошибка: минуты должны быть от 0 до 59" << endl;
    }
    
    return Time(h, m);
}

int main() {
    using namespace std;

    // Ввод времени t4 с клавиатуры
    Time t4 = inputTime("Введите время для демонстрации унарных операций:");
    cout << "Исходное время: " << t4 << endl;
    
    cout << "++t4: " << ++t4 << endl;
    
    cout << "--t4: " << --t4 << endl;
    
    cout << "\nОсобые случаи:" << endl;
    Time t5(23, 59);
    cout << "++(23:59) = " << ++t5 << endl;
    
    Time t6(0, 0);
    cout << "--(00:00) = " << --t6 << endl;
    
    // Ввод времени t7 с клавиатуры
    Time t7 = inputTime("Введите время для демонстрации операций приведения типа:");
    Time t8(0, 0);
    
    cout << "\nВремя t7 = " << t7 << endl;
    cout << "Время t8 = " << t8 << " (фиксированное для сравнения)" << endl;
    
    // Явное приведение к short int
    cout << "Явное приведение (short int)t7: " << static_cast<short int>(t7) 
         << " часов (минуты отброшены)" << endl;
    
    cout << "Неявное приведение t7 к bool в условии if: ";
    if (t7) {
        cout << "true (часы и минуты не равны нулю)" << endl;
    } else {
        cout << "false (часы и минуты равны нулю)" << endl;
    }
    
    cout << "Неявное приведение t8 к bool в условии if: ";
    if (t8) {
        cout << "true (часы и минуты не равны нулю)" << endl;
    } else {
        cout << "false (часы и минуты равны нулю)" << endl;
    }
    
    // Операции для сложения
    Time t9 = inputTime("Введите первое время для операции сложения (time + minutes):");
    
    int addMins1;
    while (true) {
        addMins1 = inputInt("Сколько минут добавить? ");
        if (addMins1 >= 0) break;
        cout << "Ошибка: количество минут не может быть отрицательным" << endl;
    }
    
    unsigned int mins1 = static_cast<unsigned int>(addMins1);
    Time result2 = t9 + mins1;
    cout << t9 << " + " << mins1 << " = " << result2 << endl;
    
    // Для вычитания
    cout << "\n";
    Time t10 = inputTime("Введите второе время для операции вычитания (time - minutes):");
    
    int subMins1;
    while (true) {
        subMins1 = inputInt("Сколько минут вычесть? ");
        if (subMins1 >= 0) break;
        cout << "Ошибка: количество минут не может быть отрицательным" << endl;
    }
    
    unsigned int mins2 = static_cast<unsigned int>(subMins1);
    Time result3 = t10 - mins2;
    cout << t10 << " - " << mins2 << " = " << result3 << endl;
    
    // Отрицательный результат (переход через полночь)
    cout << "\nПример перехода через полночь" << endl;
    Time t11(0, 15);
    unsigned int mins3 = 30u;
    Time result4 = t11 - mins3;
    cout << t11 << " - " << mins3 << " = " << result4 << endl;
    
    // Дополнительный пример: сложение с переходом через сутки
    cout << "\nПример сложения с переходом через сутки" << endl;
    Time t12(23, 30);
    unsigned int mins4 = 60u;
    Time result5 = t12 + mins4;
    cout << t12 << " + " << mins4 << " = " << result5 << endl;
    
    return 0;
}
