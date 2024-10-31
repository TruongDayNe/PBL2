#pragma once 
#include "ThanhToan.h"
#include <fstream>
#include <iostream>
#include "../Library/Console.cpp"
using namespace std;

#include "ThanhToan.h"

// Constructor mặc định
ThanhToan::ThanhToan()
    : ID_ThanhToan(""), soTienThanhToan(0), thoiGianThanhToan(""), Ve(Ticket()) {
    // Khởi tạo các giá trị mặc định
}

// Constructor có tham số
ThanhToan::ThanhToan(string id, unsigned int soTien, const Ticket& ticket)
    : ID_ThanhToan(id), thoiGianThanhToan(currentDateTime()), soTienThanhToan(soTien), Ve(ticket) {}

// Constructor sao chép
ThanhToan::ThanhToan(const ThanhToan& other)
    : ID_ThanhToan(other.ID_ThanhToan), soTienThanhToan(other.soTienThanhToan),
      thoiGianThanhToan(other.thoiGianThanhToan), Ve(other.Ve) {}

// Toán tử gán
ThanhToan& ThanhToan::operator=(const ThanhToan& other) {
    if (this != &other) {
        ID_ThanhToan = other.ID_ThanhToan;
        soTienThanhToan = other.soTienThanhToan;
        thoiGianThanhToan = other.thoiGianThanhToan;
    }
    return *this;
}

// Destructor
ThanhToan::~ThanhToan() {
}

// Getter cho ngày xuất vé
string ThanhToan::getngayXuatve() {
    return this->thoiGianThanhToan;  
}


