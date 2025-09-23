#include <iostream>
#include <string>
using namespace std;

string chet(int x) {
    string result = "";
    
    for (int i = 0; i <= x; i += 2) {
        result += to_string(i);
        if (i + 2 <= x) {
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
    
    cout << chet(x) << endl;
    
    return 0;
}