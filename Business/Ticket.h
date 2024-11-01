#pragma once
#ifndef TICKET_H
#define TICKET_H
#include <iostream>
#include <string>
#include <fstream>

class Ticket
{
private:
    int ID_ve;
    std::string ID_chuyenBay;
    std::string loaiVe;
    std::string diemDi;
    std::string diemDen;
    std::string ngayKhoiHanh;
    int soLuongVe;
    int giaVe;
public:
    // Constructor
    Ticket();
    Ticket(int, std::string, std::string, std::string, std::string, std::string, int, int);
    Ticket(const Ticket&);

    // Overloading the assignment operator
    Ticket& operator = (const Ticket&);

    // Destructor
    ~Ticket();

    // Get, Set ID_ve
    int getID_ve();
    void setID_ve(int);

    // Get, Set ID_chuyenBay
    std::string getID_chuyenBay();
    void setID_chuyenBay(std::string);

    // Get, Set loaiVe
    std::string getloaiVe();
    void setloaiVe(std::string);

    //Get, Set diemDi
    std::string getdiemDi();
    void setdiemDi(std::string);

    //Get, Set diemDen
    std::string getdiemDen();
    void setdiemDen(std::string);

    // Get, Set ngayKhoiHanh
    std::string getngayKhoiHanh();
    void setngayKhoiHanh(std::string);

    // Get, Set soLuongVe
    int getsoLuongVe();
    void setsoLuongVe(int);

    // Get, Set giaVe
    int getgiaVe();
    void setgiaVe(int);
};
#endif