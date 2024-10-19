#include "Time.h"
#include <iomanip>

// Hàm dựng
Time::Time(int h, int m, int s) : hour(h), minute(m), second(s) {}

// Tăng 1 giây
Time& Time::operator++() {
    if (++second >= 60) {
        second = 0;
        if (++minute >= 60) {
            minute = 0;
            if (++hour >= 24) {
                hour = 0;
            }
        }
    }
    return *this;
}

// Giảm 1 giây
Time& Time::operator--() {
    if (--second < 0) {
        second = 59;
        if (--minute < 0) {
            minute = 59;
            if (--hour < 0) {
                hour = 23;
            }
        }
    }
    return *this;
}

// Nhập từ luồng
std::istream& operator>>(std::istream& in, Time& time) {
    std::cout << "Enter hour/minute/second: ";
    in >> time.hour >> time.minute >> time.second;
    return in;
}

// Xuất ra luồng
std::ostream& operator<<(std::ostream& out, const Time& time) {
    out << std::setw(2) << std::setfill('0') << time.hour << ":"
        << std::setw(2) << std::setfill('0') << time.minute << ":"
        << std::setw(2) << std::setfill('0') << time.second;
    return out;
}
