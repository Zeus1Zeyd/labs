#include <iostream>
using namespace std;

int abs(int x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

int main() {
    int x;
    cout << "введите целое число: ";
    
    if (!(cin >> x)) {
        cout << "ошибка ввода. неверный формат числа." << endl;
        return 1;
    }
    
    cout << "модуль числа: " << abs(x) << endl;
    
    return 0;
}