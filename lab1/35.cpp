#include <iostream>
using namespace std;

int * add(int arr[], int ins[], int pos) {
    int len_arr = 0;
    int len_ins = 0;
    
    while (arr[len_arr] != '\0') {
        len_arr++;
    }
    
    while (ins[len_ins] != '\0') {
        len_ins++;
    }
    
    int new_len = len_arr + len_ins;
    int *new_arr = new int[new_len + 1];
    
    for (int i = 0; i < pos; i++) {
        new_arr[i] = arr[i];
    }
    
    for (int i = 0; i < len_ins; i++) {
        new_arr[pos + i] = ins[i];
    }
    
    for (int i = pos; i < len_arr; i++) {
        new_arr[i + len_ins] = arr[i];
    }
    
    return new_arr;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, '\0'};
    int ins[] = {7, 8, 9, '\0'};
    int pos = 3;
    
    int *result = add(arr, ins, pos);
    
    for (int i = 0; result[i] != '\0'; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    
    return 0;
}