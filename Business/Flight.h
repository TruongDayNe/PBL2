#pragma once

#ifndef FLIGHT_H
#define FLIGHT_H
#include <iostream>
#include <string>
#include <fstream>
#include "../LinkedList.h"

class Ticket;

class Flight
{
private:
    std::string ID_chuyenBay;
    std::string diemDi;
    std::string diemDen;
    std::string ngayKhoiHanh;
    int soLuongVe;
    int giaVe;
public:
    LinkedList<Ticket> tickets;
    // Constructor
    Flight();
    Flight(std::string, std::string, std::string, std::string, int, int);
    Flight(const Flight&);

    // Overloading the assignment operator
    Flight& operator = (const Flight&);

    // Destructor
    ~Flight();

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