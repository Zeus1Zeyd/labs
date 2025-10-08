// Дан список L с четным количеством элементов. Скопировать в конец списка все элементы,
// расположенные в его первой половине, заменив при этом отрицательные элементы на нули и
// расположив скопированные элементы в обратном порядке. Использовать алгоритм
// replace_copy_if, итератор вставки и обратные итераторы, а также функцию advance
#include <iostream>
#include <list>
#include <algorithm> // Для replace_copy_if
#include <iterator>  // Для advance
using namespace std;

// Функция для вывода списка
void printList(const list<int>& lst) {
    for (const auto& el : lst) {
        cout << el << " ";
    }
    cout << endl;
}

// Функция для выполнения задачи
void copyAndModifyList(list<int>& L) {
    // Определяем итератор на середину списка
    auto mid = L.begin();
    advance(mid, L.size() / 2);  // Перемещаем итератор на середину списка

    // Используем replace_copy_if для копирования первой половины с заменой отрицательных чисел на 0
    list<int> temp;
    replace_copy_if(L.begin(), mid, back_inserter(temp), [](int n) { return n < 0; }, 0);

    // Добавляем скопированные элементы в конец списка, используя обратный порядок
    L.insert(L.end(), temp.rbegin(), temp.rend());
}

int main() {
    list<int> L;
    size_t n;
    
    // Ввод количества элементов в деке
    cout << "Введите количество элементов в списке: ";
    cin >> n;

    cout << "Введите " << n << " элементов для списка: ";
    
    // Ввод элементов для списка
    for (size_t i = 0; i < n; ++i) {
        int num;
        cin >> num;
        L.push_back(num);
    }

    // Вывод исходного списка
    cout << "\nИсходный список: ";
    printList(L);

    // Выполняем задачу
    copyAndModifyList(L);

    // Вывод измененного списка
    cout << "Измененный список: ";
    printList(L);

    return 0;
}
