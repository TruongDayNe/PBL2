#include "Date.h"
#include <iomanip>

// Hàm dựng
Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

// Kiểm tra năm nhuận
bool Date::isLeapYear() const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Số ngày trong tháng
int Date::daysInMonth() const {
    int daysPerMonth[] = { 31, isLeapYear() ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return daysPerMonth[month - 1];
}

// Tăng 1 ngày
Date& Date::operator++() {
    if (++day > daysInMonth()) {
        day = 1;
        if (++month > 12) {
            month = 1;
            ++year;
        }
    }
    return *this;
}

// Giảm 1 ngày
Date& Date::operator--() {
    if (--day < 1) {
        if (--month < 1) {
            month = 12;
            --year;
        }
        day = daysInMonth();
    }
    return *this;
}

// Nhập từ luồng
std::istream& operator>>(std::istream& in, Date& date) {
    std::cout << "Enter day/month/year: ";
    in >> date.day >> date.month >> date.year;
    return in;
}

// Xuất ra luồng
std::ostream& operator<<(std::ostream& out, const Date& date) {
    out << std::setw(2) << std::setfill('0') << date.day << "/"
        << std::setw(2) << std::setfill('0') << date.month << "/"
        << date.year;
    return out;
}
