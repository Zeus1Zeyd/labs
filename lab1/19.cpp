#include <iostream>
#include <string>
using namespace std;

string day(int x) {
    switch (x) {
        case 1: return "понедельник";
        case 2: return "вторник";
        case 3: return "среда";
        case 4: return "четверг";
        case 5: return "пятница";
        case 6: return "суббота";
        case 7: return "воскресенье";
        default: return "это не день недели";
    }
}

int main() {
    int x;
    cout << "введите номер дня недели (1-7): ";
    
    if (!(cin >> x)) {
        cout << "ошибка ввода. неверный формат числа." << endl;
        return 1;
    }
    
    cout << day(x) << endl;
    
    return 0;
}