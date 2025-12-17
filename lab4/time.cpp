#include "time.h"
#include <iostream>
#include <iomanip>

Time::Time() : hours(0), minutes(0) {}

Time::Time(unsigned char h, unsigned char m) : hours(h), minutes(m) {}

Time::Time(const Time& other) : hours(other.hours), minutes(other.minutes) {}

Time Time::addMinutes(unsigned int minutesToAdd) const {
    Time result(*this);
    
    unsigned int totalMinutes = result.minutes + minutesToAdd;
    result.minutes = totalMinutes % 60;
    result.hours = (result.hours + totalMinutes / 60) % 24;
    
    return result;
}

std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << std::setfill('0') << std::setw(2) << (int)time.hours << ":"
       << std::setfill('0') << std::setw(2) << (int)time.minutes;
    return os;
}