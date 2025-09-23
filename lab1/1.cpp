#include <iostream>
using namespace std;

double fraction(double x) {
    int intpart = (int)x;
    double res = x - intpart;
    return res;
}

int main () {
    double result;
    cout<< "введите вещественное число: ";

    if (!(cin >> result)) {
        cout << "ошибка ввода. неверный формат числа." << endl;
        return 1;
    }

    cout<< "дробная часть числа " << result << " равна " << fraction(result) << endl; 

    return 0;

}
