#include <iostream>
using namespace std;

int maxAbs(int arr[]) {
    int maxIndex = 0;
    
    for (int i = 1; arr[i] != '\0'; i++) {
        int currentAbs = arr[i];
        if (currentAbs < 0) {
            currentAbs = -currentAbs;
        }
        
        int currentMaxAbs = arr[maxIndex];
        if (currentMaxAbs < 0) {
            currentMaxAbs = -currentMaxAbs;
        }
        
        if (currentAbs > currentMaxAbs) {
            maxIndex = i;
        }
    }
    return arr[maxIndex];
}

int main() {
    int arr[] = {1, -2, -7, 4, 2, 2, 5, '\0'};
    
    int result = maxAbs(arr);
    
    cout << result << endl;
    
    return 0;
}