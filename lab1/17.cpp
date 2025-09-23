#include <iostream>
using namespace std;

int sum2(int x, int y) {
    int sum = x + y;
    if (sum >= 10 && sum <= 19) {
        return 20;
    }
    return sum;
}

int main() {
    int x, y;
    cout << "введите два целых числа через пробел: ";
    
    if (!(cin >> x >> y)) {
        cout << "ошибка ввода. неверный формат чисел." << endl;
        return 1;
    }
    
    cout << sum2(x, y) << endl;
    
    return 0;
}