#include <iostream>
#include <list>
using namespace std;

// Функция для вывода списка
void printList(const list<int>& lst) {
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

// Функция для перемещения среднего элемента из L1 в L2
void moveMiddleToEnd(list<int>& L1, list<int>& L2) {
    // Находим итератор на средний элемент списка L1
    auto middleIt = L1.begin();
    advance(middleIt, L1.size() / 2);  // Перемещаем итератор в середину

    // Перемещаем средний элемент в конец списка L2 с помощью splice
    L2.splice(L2.end(), L1, middleIt);
}

int main() {
    list<int> L1, L2;
    size_t n;

    // Ввод списка L1
    cout << "Введите количество элементов в списке L1 (нечетное число): ";
    cin >> n;

    if (n % 2 == 0) {
        cout << "Ошибка! Количество элементов в L1 должно быть нечетным." << endl;
        return 1;
    }

    cout << "Введите " << n << " элементов для списка L1: ";
    for (size_t i = 0; i < n; ++i) {
        int num;
        cin >> num;
        L1.push_back(num);
    }

    // Ввод списка L2
    cout << "Введите количество элементов в списке L2: ";
    cin >> n;

    cout << "Введите " << n << " элементов для списка L2: ";
    for (size_t i = 0; i < n; ++i) {
        int num;
        cin >> num;
        L2.push_back(num);
    }

    cout << "\nИсходный список L1: ";
    printList(L1);

    cout << "Исходный список L2: ";
    printList(L2);

    // Перемещаем средний элемент из L1 в L2
    moveMiddleToEnd(L1, L2);

    cout << "\nИзмененный список L1: ";
    printList(L1);

    cout << "Измененный список L2: ";
    printList(L2);

    return 0;
}
