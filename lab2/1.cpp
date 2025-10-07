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

// Функция для решения задачи
void rearrangeVector(vector<int>& V) {
    // Определяем размер вектора
    size_t n = V.size();

    // Разделяем вектор на две половины
    vector<int> second_half(V.begin() + n / 2, V.end()); // Вторая половина
    vector<int> first_half(V.begin(), V.begin() + n / 2); // Первая половина

    // Сначала выводим вторую половину
    printVector(second_half);

    // Затем первую половину
    printVector(first_half);
}

int main() {
    // Ввод данных
    size_t n;
    cout << "Введите количество элементов (четное число): ";
    
    // Проверка, что ввод действительно целое число
    if (!(cin >> n)) {
        cout << "Ошибка ввода. Количество элементов должно быть целым числом." << endl;
        return 1;
    }
    
    // Проверка на четность числа
    if (n % 2 != 0) {
        cout << "Ошибка ввода. Количество элементов должно быть четным." << endl;
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
    
    // Проверка, что введено ровно n чисел
    if (V.size() != n) {
        cout << "Ошибка: введено неверное количество чисел." << endl;
        return 1;
    }
    
    // Вызываем функцию для перестановки и вывода
    rearrangeVector(V);

    return 0;
}
