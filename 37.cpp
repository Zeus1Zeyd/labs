#include <iostream>
using namespace std;

int* reverseBack(int arr[]) {
    int length = 0;
    for (int i = 0; arr[i] != '\0'; i++) {
        length++;
    }
    
    int* newArr = new int[length + 1];
    
    for (int i = 0; i < length; i++) {
        newArr[i] = arr[length - 1 - i];
    }
    
    newArr[length] = '\0';
    
    return newArr;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, '\0'};
    
    int* result = reverseBack(arr);
    
    for (int i = 0; result[i] != '\0'; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    
    return 0;
}