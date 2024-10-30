#pragma once
#include <iostream>
#include <string>
using namespace std;

class Ticket
{
private:
    int _ID;
    string _Name;
    string _Disease;
    int _Quantity;
    int _Price;
    int _Sale;
    string _Description;
public:
    // Constructor
    Ticket();
    Ticket(int, string, string, int, int, int);
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

    // Get, Set soLuongVe
    int getsoLuongVe();
    void setsoLuongVe(int);

    // Get, Set giaVe
    int getgiaVe();
    void setgiaVe(int);

    // Get, Set soGhe
    int getsoGhe();
    void setsoGhe(int);

};