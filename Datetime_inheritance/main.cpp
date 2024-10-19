#include <iostream>
#include "Date.h"
#include "Time.h"
#include "DateTime.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    Date date(28, 2, 2024); // Năm nhuận
    Time time(23, 59, 58);
    DateTime datetime(31, 12, 2023, 23, 59, 58);

    std::cout << "Ngày: " << date << std::endl;
    std::cout << "Giờ: " << time << std::endl;
    std::cout << "Ngày - Giờ: " << datetime << std::endl;

    // Tăng và giảm
    ++date;
    ++time;
    ++datetime;

    std::cout << "\nsau khi tăng:\n";
    std::cout << "Ngày: " << date << std::endl;
    std::cout << "Giờ: " << time << std::endl;
    std::cout << "Ngày - Giờ: " << datetime << std::endl;

    --date;
    --time;
    --datetime;

    std::cout << "\nSau khi giảm:\n";
    std::cout << "Ngày: " << date << std::endl;
    std::cout << "Giờ: " << time << std::endl;
    std::cout << "Ngày - Giờ: " << datetime << std::endl;

    return 0;
}
