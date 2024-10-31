
#pragma once
#include "Ticket.h"
#include <fstream>
#include <iostream>
using namespace std;

Ticket::Ticket()
{
    this->ID_ve = 0;
    this->ID_chuyenBay = " ";
    this->diemDi = " ";
    this->diemDen = " ";
    this->loaiVe = " ";
    this->ngayKhoiHanh = "";
    this->soLuongVe = 0;
    this->giaVe = 0;
}

Ticket::Ticket(int ID_ve, string ID_chuyenBay, string diemDi, string diemDen, string loaive,string ngayKhoiHanh, int soLuongVe, int giaVe)
{
    this->ID_ve = ID_ve;
    this->ID_chuyenBay = ID_chuyenBay;
    this->diemDi = loaiVe;
    this->diemDen = diemDen;
    this->loaiVe = diemDi;
    this->ngayKhoiHanh = "";
    this->soLuongVe = soLuongVe;
    this->giaVe = giaVe;
}

Ticket::Ticket(const Ticket& Ve)
{
    this->ID_ve = Ve.ID_ve;
    this->ID_chuyenBay = Ve.ID_chuyenBay;
    this->diemDi = Ve.loaiVe;
    this->diemDen = Ve.diemDen;
    this->loaiVe = Ve.diemDi;
    this->ngayKhoiHanh = Ve.ngayKhoiHanh;
    this->soLuongVe = Ve.soLuongVe;
    this->giaVe = Ve.giaVe;
}

Ticket& Ticket::operator = (const Ticket& Ve)
{
    this->ID_ve = Ve.ID_ve;
    this->ID_chuyenBay = Ve.ID_chuyenBay;
    this->diemDi = Ve.loaiVe;
    this->diemDen = Ve.diemDen;
    this->loaiVe = Ve.diemDi;
    this->ngayKhoiHanh = Ve.ngayKhoiHanh;
    this->soLuongVe = Ve.soLuongVe;
    this->giaVe = Ve.giaVe;
    return *this;
}

Ticket::~Ticket()
{

}

int Ticket::getID_ve()
{
    return this->ID_ve;
}

void Ticket::setID_ve(int id)
{
    this->ID_ve = id;
}

string Ticket::getID_chuyenBay()
{
    return this->ID_chuyenBay;
}

void Ticket::setID_chuyenBay(string ID_chuyenBay)
{
    this->ID_chuyenBay = ID_chuyenBay;
}

string Ticket::getdiemDi()
{
    return this->diemDi;
}

void Ticket::setdiemDi(string diemDi)
{
    this->diemDi = diemDi;
}

string Ticket::getdiemDen()
{
    return this->diemDen;
}

void Ticket::setdiemDen(string diemDen)
{
    this->diemDen= diemDen;
}

void Ticket::setloaiVe(string diemDen)
{
    this->diemDen = diemDen;
}

string Ticket::getloaiVe()
{
    return this->loaiVe;
}


void Ticket::setloaiVe(string loaiVe)
{
    this->loaiVe = loaiVe;
}

string Ticket::getngayKhoiHanh()
{
    return this->ngayKhoiHanh;
}

void Ticket::setngayKhoiHanh(string ngayKhoiHanh)
{
    this->ngayKhoiHanh = ngayKhoiHanh;
}


int Ticket::getsoLuongVe()
{
    return this->soLuongVe;
}

void Ticket::setsoLuongVe(int soLuongVe)
{
    this->soLuongVe = soLuongVe;
}

int Ticket::getgiaVe()
{
    return this->giaVe;
}

void Ticket::setgiaVe(int giaVe)
{
    this->giaVe = giaVe;
}
