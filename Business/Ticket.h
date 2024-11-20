#pragma once
#ifndef TICKET_H
#define TICKET_H
#include <iostream>
#include <string>
#include <fstream>
#include <Flight.h>
#include <KhachHang.h>

class Ticket
{
private:
    std::string ID_ve;
    Flight* chuyenBay;
    KhachHang* khachHang;
    std::string ghe;
    double giaVe;

public:
    // Constructor
    Ticket();
    Ticket(std::string, Flight, KhachHang, std::string, int);
    Ticket(const Ticket&);

    // Overloading the assignment operator
    Ticket& operator = (const Ticket&);

    // Destructor
    ~Ticket();

    // Get, Set ID_ve
    std::string getID_ve();
    void setID_ve(std::string);

    // // Get, Set loaiVe
    // std::string getloaiVe();
    // void setloaiVe(std::string);

    // Get, Set giaVe
    int getgiaVe();
    void setgiaVe(int);
};
#endif