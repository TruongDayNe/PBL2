#pragma once
#include <iostream>
#include "Ticket.h"
#include "KhachHang.h"
#include "../Library/Console.cpp"

using namespace std;

class ThanhToan : public Ticket {
    private:
        string ID_ThanhToan;
        unsigned int soTienThanhToan;
        string thoiGianThanhToan;
        const Ticket& Ve; 
    public:
        ThanhToan();
        ThanhToan(string , unsigned int, const Ticket&);
        ThanhToan(const ThanhToan&);

        // Overloading the assignment operator
        ThanhToan& operator = (const ThanhToan&);

        ~ThanhToan();

        string getngayXuatve();
        
        // string getngayKhoiHanh(); kế thừa từ lớp Ticket


};