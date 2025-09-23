#include <iostream>
using namespace std;

int* findAll(int arr[], int x) {
    int count = 0;
    for (int i = 0; arr[i] != '\0'; i++) {
        if (arr[i] == x) {
            count++;
        }
    }
    
    int* result = new int[count + 1];
    
    int index = 0;
    for (int i = 0; arr[i] != '\0'; i++) {
        if (arr[i] == x) {
            result[index] = i;
            index++;
        }
    }
    
    result[count] = '\0';
    
    return result;
}

int main() {
    int arr[] = {1, 2, 3, 8, 2, 2, 9, '\0'};
    int x = 2;
    
    int* result = findAll(arr, x);
    
    cout << "Индексы вхождений: ";
    for (int i = 0; result[i] != '\0'; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    
    return 0;
}