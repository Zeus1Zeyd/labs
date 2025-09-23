#include <iostream>
using namespace std;

void rightTriangle(int x) {
    for (int i = 1; i <= x; i++) {
        for (int j = 0; j < x - i; j++) {
            cout << ' ';
        }
        for (int j = 0; j < i; j++) {
            cout << '*';
        }
        cout << endl;
    }
}

int main() {
    int x;
    cout << "введите целое число: ";
    
    if (!(cin >> x)) {
        cout << "ошибка ввода. неверный формат числа." << endl;
        return 1;
    }
    
    if (x < 0) {
        cout << "ошибка: число должно быть неотрицательным." << endl;
        return 1;
    }
    
    rightTriangle(x);
    
    return 0;
}