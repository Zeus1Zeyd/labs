#include "Time.h"
#include <iostream>
#include <iomanip>

Time::Time() : hours(0), minutes(0) {}

Time::Time(unsigned char h, unsigned char m) : hours(h), minutes(m) {
    if (minutes >= 60) {
        hours += minutes / 60;
        minutes %= 60;
    }
    if (hours >= 24) {
        hours %= 24;
    }
}

Time::Time(const Time& other) : hours(other.hours), minutes(other.minutes) {}

Time Time::addMinutes(unsigned int minutesToAdd) const {
    Time result(*this);
    
    unsigned int totalMinutes = result.minutes + minutesToAdd;
    result.minutes = totalMinutes % 60;
    result.hours = (result.hours + totalMinutes / 60) % 24;
    
    return result;
}

Time& Time::operator++() {
    minutes++;
    if (minutes >= 60) {
        minutes = 0;
        hours++;
        if (hours >= 24) {
            hours = 0;
        }
    }
    return *this;
}

Time& Time::operator--() {
    if (minutes == 0) {
        minutes = 59;
        if (hours == 0) {
            hours = 23;
        } else {
            hours--;
        }
    } else {
        minutes--;
    }
    return *this;
}

// Явное приведение к short int (только часы)
Time::operator short int() const {
    return static_cast<short int>(hours);
}

// Неявное приведение к bool
Time::operator bool() const {
    return (hours != 0 || minutes != 0);
}

// Бинарная операция: time + minutes
Time Time::operator+(unsigned int minutesToAdd) const {
    return this->addMinutes(minutesToAdd);
}

// Бинарная операция: time - minutes
Time Time::operator-(unsigned int minutesToSubtract) const {
    Time result(*this);
    
    // Вычитаем минуты
    int totalMinutes = result.hours * 60 + result.minutes;
    totalMinutes -= minutesToSubtract;
    
    // Обрабатываем отрицательный результат
    if (totalMinutes < 0) {
        totalMinutes = 1440 + (totalMinutes % 1440);
    }
    
    result.hours = (totalMinutes / 60) % 24;
    result.minutes = totalMinutes % 60;
    
    return result;
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << std::setfill('0') << std::setw(2) << (int)time.hours << ":"
       << std::setfill('0') << std::setw(2) << (int)time.minutes;
    return os;
}