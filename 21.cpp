#include <iostream>
#include <string>
using namespace std;

string listNums(int x) {
    string result = "";
    
    for (int i = 0; i <= x; i++) {
        result += to_string(i);
        if (i != x) {
            result += " ";
        }
    }
    
    return result;
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
    
    cout << listNums(x) << endl;
    
    return 0;
}