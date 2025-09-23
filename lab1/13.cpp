#include <iostream>
using namespace std;

bool is35(int x) {
    if ((x % 3 == 0 && x % 5 != 0) || (x % 5 == 0 && x % 3 != 0)) {
        return true;
    }
    return false;
}

int main() {
    int x;
    cout << "введите целое число: ";
    
    if (!(cin >> x)) {
        cout << "ошибка ввода. неверный формат числа." << endl;
        return 1;
    }
    
    cout << boolalpha << is35(x) << endl;
    
    return 0;
}