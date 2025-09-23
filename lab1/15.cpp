#include <iostream>
using namespace std;

int max3(int x, int y, int z) {
    int max = x;
    
    if (y > max) {
        max = y;
    }
    
    if (z > max) {
        max = z;
    }
    
    return max;
}

int main() {
    int x, y, z;
    cout << "введите три целых числа через пробел: ";
    
    if (!(cin >> x >> y >> z)) {
        cout << "ошибка ввода. неверный формат чисел." << endl;
        return 1;
    }
    
    cout << "максимальное число: " << max3(x, y, z) << endl;
    
    return 0;
}