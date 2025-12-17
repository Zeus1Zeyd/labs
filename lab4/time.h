#ifndef TIME_H
#define TIME_H

#include <iostream>

class Time {
private:
    unsigned char hours;
    unsigned char minutes;
    
public:
    Time();
    Time(unsigned char h, unsigned char m);
    Time(const Time& other);
    
    Time addMinutes(unsigned int minutesToAdd) const;
    
    friend std::ostream& operator<<(std::ostream& os, const Time& time);
};

#endif
