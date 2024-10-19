#ifndef DATETIME_H
#define DATETIME_H

#include "Date.h"
#include "Time.h"

class DateTime : public Date, public Time {
public:
    DateTime(int d = 1, int m = 1, int y = 2000, int h = 0, int min = 0, int s = 0);
    
    DateTime& operator++();
    DateTime& operator--();

    friend std::istream& operator>>(std::istream& in, DateTime& dt);
    friend std::ostream& operator<<(std::ostream& out, const DateTime& dt);
};

#endif
