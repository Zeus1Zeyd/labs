#include <iostream>
using namespace std;

void square(int x) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < x; j++) {
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
    
    square(x);
    
    return 0;
}