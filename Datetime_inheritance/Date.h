#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date {
protected:
    int day, month, year;

public:
    Date(int d = 1, int m = 1, int y = 2000);
    
    bool isLeapYear() const;
    int daysInMonth() const;

    Date& operator++();
    Date& operator--();

    friend std::istream& operator>>(std::istream& in, Date& date);
    friend std::ostream& operator<<(std::ostream& out, const Date& date);
};

#endif
