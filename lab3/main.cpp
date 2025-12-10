#include <iostream>
#include <vector>
#include <limits>
#include "point.h"
#include "line.h"
#include "student.h"
#include <sstream>

using namespace std;

double inputDouble(const string& prompt) {
    string input;  // считываем всю строку
    double value;
    
    while (true) {
        cout << prompt;
        
        // Считываем всю строку
        getline(cin, input);
        
        // Проверяем, не пустая ли строка
        if (input.empty()) {
            cout << "Ошибка: пустой ввод. Пожалуйста, введите число." << endl;
            continue;
        }
        
        // пробуем преобразовать строку в число
        stringstream ss(input);
        
        // пробуем считать число
        if (ss >> value) {
            // проверяем, не осталось ли чего-то в строке после числа
            string remaining;
            if (ss >> remaining) {
                // В строке есть что-то после числа
                cout << "Ошибка: введены лишние символы: " << remaining << endl;
            } else {
                return value;
            }
        } else {
            cout << "Ошибка: '" << input << "' не является числом. "
                 << "Пожалуйста, введите число." << endl;
        }
    }
}

int inputInt(const string& prompt) {
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
                cout << "Ошибка: введены лишние символы: '" << remaining;
            } else {
                return value;
            }
        } else {
            cout << "Ошибка: '" << input << "' не является целым числом." << endl;
        }
    }
}

vector<int> inputGrades() {
    vector<int> grades;
    int count = inputInt("Введите количество оценок: ");
    
    for (int i = 0; i < count; i++) {
        int grade = inputInt("Введите оценку " + to_string(i+1) + ": ");
        grades.push_back(grade);
    }
    
    return grades;
}

void task1() {
    cout << "ЗАДАНИЕ 1" << endl;
    
    cout << "\nВведите координаты трех точек:" << endl;
    
    cout << "\nТочка 1:" << endl;
    double x1 = inputDouble("X: ");
    double y1 = inputDouble("Y: ");
    Point point1(x1, y1);
    
    cout << "\nТочка 2:" << endl;
    double x2 = inputDouble("X: ");
    double y2 = inputDouble("Y: ");
    Point point2(x2, y2);
    
    cout << "\nТочка 3:" << endl;
    double x3 = inputDouble("X: ");
    double y3 = inputDouble("Y: ");
    Point point3(x3, y3);
    
    cout << "\nТекстовое представление точек:" << endl;
    cout << "Точка 1: ";
    point1.print();
    cout << "Точка 2: ";
    point2.print();
    cout << "Точка 3: ";
    point3.print();
}

void task2() {
    cout << "ЗАДАНИЕ 2" << endl;
    
    cout << "\nВведите координаты для Линии 1:" << endl;
    cout << "Начальная точка:" << endl;
    double x1_start = inputDouble("X: ");
    double y1_start = inputDouble("Y: ");
    
    cout << "Конечная точка:" << endl;
    double x1_end = inputDouble("X: ");
    double y1_end = inputDouble("Y: ");
    
    Point* start1 = new Point(x1_start, y1_start);
    Point* end1 = new Point(x1_end, y1_end);
    
    cout << "\nВведите координаты для горизонтальной Линии 2:" << endl;
    cout << "Введите высоту (Y координата, одинаковая для начала и конца): ";
    double y2 = inputDouble("Y: ");
    
    cout << "Введите координату X для начала линии: ";
    double x2_start = inputDouble("X начала: ");
    
    cout << "Введите координату X для конца линии: ";
    double x2_end = inputDouble("X конца: ");
    
    Point* start2 = new Point(x2_start, y2);
    Point* end2 = new Point(x2_end, y2);
    
    Line line1(start1, end1);
    Line line2(start2, end2);
    
    Line line3(start1, end2);
    
    cout << "\nСозданные линии:" << endl;
    cout << "Линия 1: ";
    line1.print();
    cout << "Линия 2: ";
    line2.print();
    cout << "Линия 3 (связана с 1 и 2): ";
    line3.print();
    
    cout << "\n--- Изменение координат ---" << endl;
    cout << "Введите новые координаты для Линии 1:" << endl;
    cout << "Новая начальная точка:" << endl;
    double new_x1_start = inputDouble("X: ");
    double new_y1_start = inputDouble("Y: ");
    
    cout << "Новая конечная точка:" << endl;
    double new_x1_end = inputDouble("X: ");
    double new_y1_end = inputDouble("Y: ");
    
    start1->setX(new_x1_start);
    start1->setY(new_y1_start);
    end1->setX(new_x1_end);
    end1->setY(new_y1_end);
    
    cout << "\nВведите новые координаты для Линии 2:" << endl;
    cout << "Новая высота (Y координата): ";
    double new_y2 = inputDouble("Y: ");
    
    cout << "Новое начало (X координата): ";
    double new_x2_start = inputDouble("X: ");
    
    cout << "Новый конец (X координата): ";
    double new_x2_end = inputDouble("X: ");
    
    start2->setX(new_x2_start);
    start2->setY(new_y2);
    end2->setX(new_x2_end);
    end2->setY(new_y2);
    
    cout << "\nПосле изменения:" << endl;
    cout << "Линия 1: ";
    line1.print();
    cout << "Линия 2: ";
    line2.print();
    cout << "Линия 3 (автоматически изменилась): ";
    line3.print();
    
    // изменение координат первой линии без изменения третьей
    cout << "\n--- Создаем новые точки для Линии 1 ---" << endl;
    cout << "Введите новые координаты для ЛИНИИ 1 (только для нее):" << endl;
    
    cout << "Конечная точка:" << endl;
    double sep_x1_end = inputDouble("X: ");
    double sep_y1_end = inputDouble("Y: ");
    
    Point* newEnd1 = new Point(sep_x1_end, sep_y1_end);
    
    // присваиваем только линии 1
    line1.setEndPoint(newEnd1);
    
    cout << "\nПосле изменения только Линии 1:" << endl;
    cout << "Линия 1: ";
    line1.print();
    cout << "Линия 3 (НЕ изменилась): ";
    line3.print();
    
    delete start1;
    delete end1;
    delete start2;
    delete end2;
    delete newEnd1;
}

void task3() {
    cout << "ЗАДАНИЕ 3" << endl;
    
    // вася с оценками
    cout << "\n1. Создание студента Васи:" << endl;
    string name1 = "Вася";
    cout << "Введите оценки для Васи:" << endl;
    vector<int> vasyaGrades = inputGrades();
    Student vasya(name1, vasyaGrades);
    
    cout << "\nСоздан студент Вася: ";
    vasya.print();
    
    // петя с оценками васи
    cout << "\n2. Создание студента Пети (копирование оценок Васи):" << endl;
    string name2 = "Петя";
    vector<int> petyaGrades = vasya.getGrades();
    Student petya(name2, petyaGrades);
    
    cout << "Создан студент Петя: ";
    petya.print();
    
    // замена первой оценки Пети
    cout << "\n3. Замена первой оценки Пети:" << endl;
    cout << "Введите новую первую оценку для Пети: ";
    int newFirstGrade = inputInt("Новая оценка: ");
    
    vector<int> newPetyaGrades = petya.getGrades();
    if (!newPetyaGrades.empty()) {
        newPetyaGrades[0] = newFirstGrade;
        petya.setGrades(newPetyaGrades);
    }
    
    cout << "\nПосле изменения первой оценки Пети:" << endl;
    cout << "Вася: ";
    vasya.print();
    cout << "Петя: ";
    petya.print();
    
    cout << "\n4. Создание студента Андрея (глубокое копирование):" << endl;
    string name3 = "Андрей";
    
    // новые оценки для Васи
    cout << "\nВведите НОВЫЕ оценки для Васи: " << endl;
    vector<int> newVasyaGrades = inputGrades();
    vasya.setGrades(newVasyaGrades);
    
    // Андрей с текущими оценками Васи
    vector<int> andreyGrades = vasya.getGrades();
    Student andrey(name3, andreyGrades);
    
    cout << "\nПосле изменения оценок Васи и создания Андрея:" << endl;
    cout << "Вася: ";
    vasya.print();
    cout << "Андрей: ";
    andrey.print();
    
    cout << "\nОбъяснение: У Андрея создана копия вектора оценок Васи, ";
    cout << "поэтому дальнейшее изменение оценок Васи не повлияет на Андрея." << endl;
}

void task4_1() {
    cout << "ЗАДАНИЕ 4.1: СОЗДАЕМ ТОЧКУ" << endl;
    
    cout << "\nСоздаем точки с координатами:" << endl;
    
    Point point1(3, 5);
    cout << "Точка 1 (3;5): ";
    point1.print();
    
    Point point2(25, 6);
    cout << "Точка 2 (25;6): ";
    point2.print();
    
    Point point3(7, 8);
    cout << "Точка 3 (7;8): ";
    point3.print();
}

void task4_2() {
    cout << "ЗАДАНИЕ 4.2" << endl;
    
    cout << "Введите данные для создания линий:" << endl;
    
    cout << "\n1. Линия 1 (через объекты Point):" << endl;
    cout << "Введите координаты начала:" << endl;
    double l1_x1 = inputDouble("X: ");
    double l1_y1 = inputDouble("Y: ");
    
    cout << "Введите координаты конца:" << endl;
    double l1_x2 = inputDouble("X: ");
    double l1_y2 = inputDouble("Y: ");
    
    Point start1(l1_x1, l1_y1);
    Point end1(l1_x2, l1_y2);
    Line line1(start1, end1);
    
    cout << "Линия 1: ";
    line1.print();
    
    cout << "\n2. Линия 2 (горизонтальная, через 4 числа):" << endl;
    cout << "Введите высоту (Y): ";
    double y_height = inputDouble("Y: ");
    
    cout << "Введите X начала: ";
    double l2_x1 = inputDouble("X начала: ");
    
    cout << "Введите X конца: ";
    double l2_x2 = inputDouble("X конца: ");
    
    Line line2(l2_x1, y_height, l2_x2, y_height);
    
    cout << "Линия 2: ";
    line2.print();
    
    cout << "\n3. Линия 3 (комбинация 1 и 2):" << endl;
    cout << "Начинается там же, где Линия 1, заканчивается там же, где Линия 2" << endl;
    
    Line line3(start1, Point(line2.getEndPoint()->getX(), line2.getEndPoint()->getY()));
    
    cout << "Линия 3: ";
    line3.print();
}

void task5() {
    cout << "ЗАДАНИЕ 4.3: ДЛИНА ЛИНИИ" << endl;
    
    cout << "Введите координаты для линии:" << endl;
    
    double x1 = inputDouble("Начало - X: ");
    double y1 = inputDouble("Начало - Y: ");
    double x2 = inputDouble("Конец - X: ");
    double y2 = inputDouble("Конец - Y: ");
    
    Line line(x1, y1, x2, y2);
    
    cout << "\nСозданная линия: ";
    line.print();
    
    double len = line.length();
    cout << "Длина линии: " << len << endl;
    cout << "Длина линии (целое число): " << static_cast<int>(len + 0.5) << endl;
}

int main() {
    
    task1();
    task2();
    task3();
    task4_1();
    task4_2();
    task5();
    
    return 0;
}