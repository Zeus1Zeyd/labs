#include <iostream>
using namespace std;

bool isInRange(int a, int b, int num) {
    if (a <= b) {
        if (num >= a && num <= b) {
            return true;
        }
    } else {
        if (num >= b && num <= a) {
            return true;
        }
    }
    return false;
}

int main() {
    int a, b, num;
    cout << "введите левую границу a: ";
    if (!(cin >> a)) {
        cout << "ошибка ввода. неверный формат числа." << endl;
        return 1;
    }
    
    cout << "введите правую границу b: ";
    if (!(cin >> b)) {
        cout << "ошибка ввода. неверный формат числа." << endl;
        return 1;
    }
    
    cout << "введите число для проверки: ";
    if (!(cin >> num)) {
        cout << "ошибка ввода. неверный формат числа." << endl;
        return 1;
    }
    
    cout << boolalpha << isInRange(a, b, num) << endl;
    
    return 0;
}