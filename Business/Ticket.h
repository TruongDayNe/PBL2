#pragma once
#include <iostream>
#include <string>
using namespace std;

class Ticket
{
private:
    int ID_ve;
    string ID_chuyenBay;
    string loaiVe;
    string diemDi;
    string diemDen;
    string ngayKhoiHanh;
    static int soLuongVe;
    int giaVe;
public:
    // Constructor
    Ticket();
    Ticket(int, string, string, string, string, string, int, int);
    Ticket(const Ticket&);

    // Overloading the assignment operator
    Ticket& operator = (const Ticket&);

    // Destructor
    ~Ticket();

    // Get, Set ID_ve
    int getID_ve();
    void setID_ve(int);

    // Get, Set ID_chuyenBay
    string getID_chuyenBay();
    void setID_chuyenBay(string);

    // Get, Set loaiVe
    string getloaiVe();
    void setloaiVe(string);

    //Get, Set diemDi
    string getdiemDi();
    void setdiemDi(string);

    //Get, Set diemDen
    string getdiemDen();
    void setdiemDen(string);

    // Get, Set ngayKhoiHanh
    string getngayKhoiHanh();
    void setngayKhoiHanh(string);

    // Get, Set soLuongVe
    int getsoLuongVe();
    void setsoLuongVe(int);

    // Get, Set giaVe
    int getgiaVe();
    void setgiaVe(int);
};