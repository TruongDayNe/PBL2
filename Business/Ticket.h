#pragma once
#ifndef TICKET_H
#define TICKET_H
#include <iostream>
#include <string>
#include <fstream>
#include "Flight.h"
#include "KhachHang.h"
#include "../Library/Console.h"

class Flight;
class KhachHang;

class Ticket
{
private:
    std::string ID_ve;
    Flight* chuyenBay;
    KhachHang* khachHang;
    std::string ghe;
    int giaVe;
    std::string ngayMua;
public:
    // Constructor
    Ticket();
    Ticket(std::string, Flight, KhachHang, std::string, int, std::string = currentDateTime());
    Ticket(const Ticket&);

    // Overloading the assignment operator
    Ticket& operator = (const Ticket&);

    // Destructor
    ~Ticket();

    // Get, Set ngayMua
    std::string getngayMua();
    void setngayMua(std::string);

    // Get, Set ID_ve
    std::string getID_ve();
    void setID_ve(std::string);

    Flight getChuyenBay();
    void setChuyenBay(Flight);

    KhachHang getKhachHang();
    void setKhachHang(KhachHang);

    std::string getGhe();
    void setGhe(std::string);

    // // Get, Set loaiVe
    // std::string getloaiVe();
    // void setloaiVe(std::string);

    // Get, Set giaVe
    int getgiaVe();
    void setgiaVe(int);
};
#endif