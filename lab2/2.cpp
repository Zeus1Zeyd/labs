#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

// Функция для вывода элементов вектора
void printVector(const vector<int>& vec) {
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

// Функция для вставки -1 после каждого элемента
void insertMinusOne(vector<int>& V) {
    // Используем итератор для обхода элементов вектора
    for (auto i = V.begin(); i != V.end(); ++i) {
        // Вставляем -1 после текущего элемента
        i = V.insert(++i, -1); // Вставляем -1 после текущего элемента
    }
}

int main() {
    size_t n;
    cout << "Введите количество элементов вектора: ";
    
    // Проверка, что количество элементов целое число
    if (!(cin >> n) || n <= 0) {
        cout << "Ошибка ввода. Количество элементов должно быть положительным числом." << endl;
        return 1;
    }
    
    vector<int> V;
    cout << "Введите " << n << " целых чисел: ";
    
    // Ввод элементов вектора с проверкой
    for (size_t i = 0; i < n; ++i) {
        int num;
        if (!(cin >> num)) {
            cout << "Ошибка ввода. Неверный формат числа." << endl;
            return 1;
        }
        V.push_back(num);
    }
    
    cout << "Исходный вектор: ";
    printVector(V);
    
    // Вставляем -1 после каждого элемента
    insertMinusOne(V);
    
    cout << "Измененный вектор: ";
    printVector(V);
    
    return 0;
}
