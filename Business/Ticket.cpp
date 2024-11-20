#include "Ticket.h"

// Default constructor
Ticket::Ticket() 
    : ID_ve(""), chuyenBay(nullptr), khachHang(nullptr), ghe(""), giaVe(0.0) {}

// Parameterized constructor
Ticket::Ticket(std::string ID_ve, Flight chuyenBay, KhachHang khachHang, std::string ghe, int giaVe)
    : ID_ve(ID_ve), chuyenBay(&chuyenBay), khachHang(&khachHang), ghe(ghe), giaVe(giaVe) {}

// Copy constructor
Ticket::Ticket(const Ticket& other)
    : ID_ve(other.ID_ve), chuyenBay(other.chuyenBay), khachHang(other.khachHang), ghe(other.ghe), giaVe(other.giaVe) {}

// Assignment operator
Ticket& Ticket::operator=(const Ticket& other) {
    if (this != &other) { // Kiểm tra tự gán
        ID_ve = other.ID_ve;
        chuyenBay = other.chuyenBay;   // Shallow copy
        khachHang = other.khachHang;   // Shallow copy
        ghe = other.ghe;
        giaVe = other.giaVe;
    }
    return *this;
}

// Destructor
Ticket::~Ticket() {
}

// Get ID_ve
std::string Ticket::getID_ve() {
    return ID_ve;
}

// Set ID_ve
void Ticket::setID_ve(std::string id) {
    ID_ve = id; // Chuyển đổi từ int sang string
}

// Get giaVe
int Ticket::getgiaVe() {
    return static_cast<int>(giaVe);
}

// Set giaVe
void Ticket::setgiaVe(int gia) {
    giaVe = static_cast<double>(gia);
}
