#include <iostream>
using namespace std;

int charToNum(char x) {
    int res = x - '0';
    return res;
}

int main() {
    char sym;
    cout << "введите символ цифры: ";
    
    if (!(cin >> sym)) {
        cout << "ошибка ввода" << endl;
        return 1;
    }
    
    if (sym < '0' || sym > '9') {
        cout << "введен не цифровой символ." << endl;
        return 1;
    }
    
    int result = charToNum(sym);
    cout << result << endl;
    
    return 0;
}