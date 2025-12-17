#include <iostream>
#include <sstream>
#include <string>
#include "time.h"

int inputInt(const std::string& prompt) {
    using namespace std;
    string input;
    int value;
    
    while (true) {
        cout << prompt;
        getline(cin, input);
        
        if (input.empty()) {
            cout << "Ошибка: пустой ввод. Пожалуйста, введите целое число." << endl;
            continue;
        }
        
        stringstream ss(input);
        
        if (ss >> value) {
            string remaining;
            if (ss >> remaining) {
                cout << "Ошибка: введены лишние символы: '" << remaining << "'" << endl;
            } else {
                return value;
            }
        } else {
            cout << "Ошибка: '" << input << "' не является целым числом." << endl;
        }
    }
}

int inputTimeValue(const std::string& prompt, int minVal, int maxVal) {
    using namespace std;
    int value;
    
    while (true) {
        value = inputInt(prompt);
        
        if (value >= minVal && value <= maxVal) {
            return value;
        } else {
            cout << "Ошибка: значение должно быть от " << minVal << " до " << maxVal << endl;
        }
    }
}

int main() {
    using namespace std;
    
    cout << "\nВвод начального времени:" << endl;
    int h = inputTimeValue("Часы (0-23): ", 0, 23);
    int m = inputTimeValue("Минуты (0-59): ", 0, 59);
    
    Time startTime(h, m);
    
    int addMins = inputInt("Сколько минут добавить? ");
    
    while (addMins < 0) {
        cout << "Ошибка: нельзя добавить отрицательное количество минут!" << endl;
        addMins = inputInt("Сколько минут добавить? ");
    }
    
    Time endTime = startTime.addMinutes(addMins);
    
    cout << "Начальное время: " << startTime << endl;
    cout << "Добавлено минут: " << addMins << endl;
    cout << "Итоговое время: " << endTime << endl;
    
    Time defaultT;
    Time copyTime(startTime);
    
    cout << "Время по умолчанию: " << defaultT << endl;
    cout << "Копия начального времени: " << copyTime << endl;
    
    return 0;
}