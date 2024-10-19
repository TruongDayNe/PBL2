#ifndef TIME_H
#define TIME_H

#include <iostream>

class Time {
protected:
    int hour, minute, second;

public:
    Time(int h = 0, int m = 0, int s = 0);
    
    Time& operator++();
    Time& operator--();

    friend std::istream& operator>>(std::istream& in, Time& time);
    friend std::ostream& operator<<(std::ostream& out, const Time& time);
};

#endif
