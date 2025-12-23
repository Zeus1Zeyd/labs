/**
 * @file main.cpp
 * @brief Главный файл проекта с функциями ввода и решениями всех задач
 */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "UniqueSet.h"
#include "Dictionary.h"
#include "Point3D.h"

/**
 * @brief Функция безопасного ввода целого числа
 * @param prompt Подсказка для пользователя
 * @return Введенное целое число
 */
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

/**
 * @brief Функция безопасного ввода строки
 * @param prompt Подсказка для пользователя
 * @return Введенная строка
 */
std::string inputString(const std::string& prompt) {
    using namespace std;
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

/**
 * @brief Функция безопасного ввода вещественного числа
 * @param prompt Подсказка для пользователя
 * @return Введенное вещественное число
 */
double inputDouble(const std::string& prompt) {
    using namespace std;
    string input;
    double value;
    
    while (true) {
        cout << prompt;
        getline(cin, input);
        
        if (input.empty()) {
            cout << "Ошибка: пустой ввод. Пожалуйста, введите число." << endl;
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
            cout << "Ошибка: '" << input << "' не является числом." << endl;
        }
    }
}

/**
 * @brief Решение задачи 1: Торгово-развлекательные центры
 */
void solveTask1() {
    using namespace std;
    cout << "Торгово-развлекательные центры" << endl;
    
    // Создаем перечень всех ТРЦ в городе
    UniqueSet<string> allTRC;
    
    int trcCount = inputInt("Введите количество ТРЦ в городе: ");
    for (int i = 0; i < trcCount; i++) {
        string trc = inputString("Введите название ТРЦ " + to_string(i + 1) + ": ");
        allTRC.add(trc);
    }
    
    // Создаем множества для студентов
    int studentCount = inputInt("Введите количество студентов в группе: ");
    UniqueSet<string>* studentVisits = new UniqueSet<string>[studentCount];
    
    // Для каждого студента вводим посещенные ТРЦ
    for (int i = 0; i < studentCount; i++) {
        cout << "\nСтудент " << (i + 1) << ":" << endl;
        int visitCount = inputInt("Сколько ТРЦ посетил студент: ");
        
        for (int j = 0; j < visitCount; j++) {
            string trc = inputString("ТРЦ " + to_string(j + 1) + ": ");
            studentVisits[i].add(trc);
        }
    }
    
    // Находим ТРЦ, которые посетили все студенты
    UniqueSet<string> commonTRC = studentVisits[0];
    for (int i = 1; i < studentCount; i++) {
        commonTRC = commonTRC.Intersect(studentVisits[i]);
    }
    
    // Находим ТРЦ, которые посетил хотя бы один студент
    UniqueSet<string> anyStudentTRC = studentVisits[0];
    for (int i = 1; i < studentCount; i++) {
        anyStudentTRC = anyStudentTRC.Union(studentVisits[i]);
    }
    
    // Находим ТРЦ, которые не посетил ни один студент
    UniqueSet<string> noStudentTRC = allTRC.Except(anyStudentTRC);
    
    cout << "\nВсе ТРЦ в городе:" << endl;
    allTRC.print();
    
    cout << "\nТРЦ, которые посетили ВСЕ студенты:" << endl;
    if (commonTRC.isEmpty()) {
        cout << "Нет таких ТРЦ" << endl;
    } else {
        commonTRC.print();
    }
    
    cout << "\nТРЦ, которые посетил ХОТЯ БЫ ОДИН студент:" << endl;
    if (anyStudentTRC.isEmpty()) {
        cout << "Нет таких ТРЦ" << endl;
    } else {
        anyStudentTRC.print();
    }
    
    cout << "\nТРЦ, которые НЕ посетил НИ ОДИН студент:" << endl;
    if (noStudentTRC.isEmpty()) {
        cout << "Нет таких ТРЦ" << endl;
    } else {
        noStudentTRC.print();
    }
    
    delete[] studentVisits;
}

/**
 * @brief Решение задачи 2: Генерация уникальных логинов
 */
void solveTask2() {
    using namespace std;
    cout << "Генерация уникальных логинов для учеников" << endl;
    
    Dictionary<string, int> surnameCount; // Словарь для подсчета фамилий
    ifstream inputFile("./lab6/students.txt");
    
    if (inputFile.is_open()) {
        int n;
        inputFile >> n;
        inputFile.ignore(); // Игнорируем символ новой строки
        
        cout << "\nВходные данные:" << endl;
        cout << "Количество учеников: " << n << endl;
        
        cout << "\nСгенерированные логины:" << endl;
        for (int i = 0; i < n; i++) {
            string line;
            getline(inputFile, line);
            
            // Извлекаем фамилию (первое слово до пробела)
            size_t spacePos = line.find(' ');
            string surname = line.substr(0, spacePos);
            
            // Генерируем логин
            if (!surnameCount.contains(surname)) {
                // Первое вхождение фамилии
                surnameCount.add(surname, 1);
                cout << surname << endl;
            } else {
                // Фамилия уже встречалась
                int count = surnameCount.get(surname) + 1;
                surnameCount.set(surname, count);
                cout << surname << count << endl;
            }
        }
        
        inputFile.close();
    } else {
        cout << "Не удалось открыть файл students.txt" << endl;
    }
}

/**
 * @brief Решение задачи 3: Трехмерные точки
 */
void solveTask3() {
    using namespace std;
    cout << "Работа с двухмерными и трехмерными точками" << endl;
    
    cout << "\n--- Работа с двухмерными точками ---" << endl;
    
    double x1 = inputDouble("Введите координату X первой точки: ");
    double y1 = inputDouble("Введите координату Y первой точки: ");
    Point2D p1(x1, y1);
    
    double x2 = inputDouble("Введите координату X второй точки: ");
    double y2 = inputDouble("Введите координату Y второй точки: ");
    Point2D p2(x2, y2);
    
    cout << "\nТочка 1: " << p1.toString() << endl;
    cout << "Точка 2: " << p2.toString() << endl;
    cout << "Расстояние между точками: " << p1.distanceTo(p2) << endl;
    
    cout << "\n--- Работа с трехмерными точками ---" << endl;
    
    x1 = inputDouble("Введите координату X первой 3D точки: ");
    y1 = inputDouble("Введите координату Y первой 3D точки: ");
    double z1 = inputDouble("Введите координату Z первой 3D точки: ");
    Point3D p3d1(x1, y1, z1);
    
    x2 = inputDouble("Введите координату X второй 3D точки: ");
    y2 = inputDouble("Введите координату Y второй 3D точки: ");
    double z2 = inputDouble("Введите координату Z второй 3D точки: ");
    Point3D p3d2(x2, y2, z2);
    
    cout << "\nТочка 1: " << p3d1.toString() << endl;
    cout << "Точка 2: " << p3d2.toString() << endl;
    cout << "Расстояние между 3D точками: " << p3d1.distanceTo(p3d2) << endl;
}

/**
 * @brief Главная функция программы
 * @return Код завершения программы
 */
int main() {
    using namespace std;
    
    int choice;
    do {
        cout << "\nМЕНЮ:" << endl;
        cout << "1. Задание 1 - Торгово-развлекательные центры" << endl;
        cout << "2. Задание 2 - Генерация уникальных логинов" << endl;
        cout << "3. Задание 3 - Двухмерные и трехмерные точки" << endl;
        cout << "0. Выход" << endl;
        
        choice = inputInt("Выберите пункт меню: ");
        
        switch (choice) {
            case 1:
                solveTask1();
                break;
            case 2:
                solveTask2();
                break;
            case 3:
                solveTask3();
                break;
            case 0:
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    } while (choice != 0);
    
    return 0;
}