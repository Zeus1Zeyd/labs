#include <iostream>
using namespace std;

bool is2Digits(int x) {
    if ((x >= 10 && x <= 99) || (x <= -10 && x >= -99)) {
        return true;
    }
    return false;
}

int main() {
    int number;
    cout << "введите целое число: ";
    
    if (!(cin >> number)) {
        cout << "ошибка ввода. неверный формат числа." << endl;
        return 1;
    }
    
    cout << boolalpha << is2Digits(number) << endl;
    
    return 0;
}