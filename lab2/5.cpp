// Дан дек D. Удалить последний нулевой элемент дека. Если нулевых элементов нет, то дек не
// изменять. Использовать алгоритм find с обратными итераторами и функцию-член erase.
#include <iostream>
#include <deque>
#include <algorithm> // Для find
using namespace std;

// Функция для удаления последнего нулевого элемента
void removeLastZero(deque<int>& D) {
    // Ищем последний нулевой элемент с обратным итератором
    auto r = find(D.rbegin(), D.rend(), 0);
    
    // Если элемент найден, удаляем его
    if (r != D.rend()) {
        D.erase((++r).base()); // Удаляем элемент, используя r.base() потому что обычный erase удаляет у обычного итератора
    }
}

int main() {
    deque<int> D;
    size_t n;
    
    // Ввод количества элементов в деке
    cout << "Введите количество элементов в деке: ";
    cin >> n;

    cout << "Введите " << n << " элементов для дека: ";
    
    // Ввод элементов для дека
    for (size_t i = 0; i < n; ++i) {
        int num;
        cin >> num;
        D.push_back(num);
    }

    // Вывод исходного дека
    cout << "\nИсходный дек: ";
    for (const auto& el : D) {
        cout << el << " ";
    }
    cout << endl;

    // Удаляем последний нулевой элемент
    removeLastZero(D);

    // Вывод измененного дека
    cout << "\nИзмененный дек: ";
    for (const auto& el : D) {
        cout << el << " ";
    }
    cout << endl;

    return 0;
}
