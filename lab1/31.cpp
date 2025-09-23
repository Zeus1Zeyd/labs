#include <iostream>
using namespace std;

int findFirst(int arr[], int x) {
    for (int i = 0; arr[i] != '\0'; i++) {
        if (arr[i] == x) {
            return i;
        }
    }
    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 4, 2, 2, 5};
    int x;
    
    cout << "введите число для поиска: ";
    
    if (!(cin >> x)) {
        cout << "ошибка ввода. неверный формат числа." << endl;
        return 1;
    }
    
    int result = findFirst(arr, x);
    
    if (result == -1) {
        cout << "число " << x << " не найдено в массиве." << endl;
    } else {
        cout << result << endl;
    }
    
    return 0;
}