#ifndef TIME_H
#define TIME_H

#include <iostream>

class Time {
private:
    unsigned char hours;
    unsigned char minutes;
    
public:
    // Конструкторы
    Time();
    Time(unsigned char h, unsigned char m);
    Time(const Time& other);
    
    // Метод из задания 1
    Time addMinutes(unsigned int minutesToAdd) const;
    
    // Унарные операции
    Time& operator++();      // ++time
    Time& operator--();      // --time
    
    // Операции приведения типа
    explicit operator short int() const;  // Явное приведение
    operator bool() const;                // Неявное приведение
    
    // Бинарные операции
    Time operator+(unsigned int minutes) const;  // time + minutes
    Time operator-(unsigned int minutes) const;  // time - minutes
    
    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Time& time);
};

#endif