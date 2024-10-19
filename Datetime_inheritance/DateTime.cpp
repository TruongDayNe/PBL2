#include "DateTime.h"

// Hàm dựng
DateTime::DateTime(int d, int m, int y, int h, int min, int s)
    : Date(d, m, y), Time(h, min, s) {}

// Tăng 1 giây
DateTime& DateTime::operator++() {
    Time::operator++();
    if (hour == 0 && minute == 0 && second == 0) {
        Date::operator++();
    }
    return *this;
}

// Giảm 1 giây
DateTime& DateTime::operator--() {
    Time::operator--();
    if (hour == 23 && minute == 59 && second == 59) {
        Date::operator--();
    }
    return *this;
}

// Nhập từ luồng
std::istream& operator>>(std::istream& in, DateTime& dt) {
    in >> static_cast<Date&>(dt) >> static_cast<Time&>(dt);
    return in;
}

// Xuất ra luồng
std::ostream& operator<<(std::ostream& out, const DateTime& dt) {
    out << static_cast<const Date&>(dt) << " " << static_cast<const Time&>(dt);
    return out;
}
