#include <iostream>
using namespace std;

bool isEqual(int a, int b, int c) {
    if (a == b && b == c) {
        return true;
    }
    return false;
}

int main() {
    int a, b, c;
    cout << "введите три целых числа через пробел: ";
    
    if (!(cin >> a >> b >> c)) {
        cout << "ошибка ввода. неверный формат чисел." << endl;
        return 1;
    }
    
    cout << boolalpha << isEqual(a, b, c) << endl;
    
    return 0;
}