#include <iostream>
using namespace std;

int numLen(long x) {
    if (x == 0) {
        return 1;
    }
    
    long absoluteX = x;
    if (x < 0) {
        absoluteX = -x;
    }
    
    int count = 0;
    
    while (absoluteX > 0) {
        absoluteX = absoluteX / 10;
        count++;
    }
    
    return count;
}

int main() {
    long x;
    cout << "введите целое число: ";
    
    if (!(cin >> x)) {
        cout << "ошибка ввода. неверный формат числа." << endl;
        return 1;
    }
    
    int result = numLen(x);
    cout << "количество знаков в числе: " << result << endl;
    
    return 0;
}