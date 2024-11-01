#include "Ticket.h"

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

Ticket::Ticket(int ID_ve, std::string ID_chuyenBay, std::string diemDi, std::string diemDen, std::string loaiVe, std::string ngayKhoiHanh, int soLuongVe, int giaVe)
{
    this->ID_ve = ID_ve;
    this->ID_chuyenBay = ID_chuyenBay;
    this->diemDi = diemDi;
    this->diemDen = diemDen;
    this->loaiVe = loaiVe;
    this->ngayKhoiHanh = ngayKhoiHanh;
    this->soLuongVe = soLuongVe;
    this->giaVe = giaVe;
}

Ticket::Ticket(const Ticket& Ve)
{
    this->ID_ve = Ve.ID_ve;
    this->ID_chuyenBay = Ve.ID_chuyenBay;
    this->diemDi = Ve.diemDi;
    this->diemDen = Ve.diemDen;
    this->loaiVe = Ve.loaiVe;
    this->ngayKhoiHanh = Ve.ngayKhoiHanh;
    this->soLuongVe = Ve.soLuongVe;
    this->giaVe = Ve.giaVe;
}

Ticket& Ticket::operator = (const Ticket& Ve)
{
    this->ID_ve = Ve.ID_ve;
    this->ID_chuyenBay = Ve.ID_chuyenBay;
    this->diemDi = Ve.diemDi;
    this->diemDen = Ve.diemDen;
    this->loaiVe = Ve.loaiVe;
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

std::string Ticket::getID_chuyenBay()
{
    return this->ID_chuyenBay;
}

void Ticket::setID_chuyenBay(std::string ID_chuyenBay)
{
    this->ID_chuyenBay = ID_chuyenBay;
}

std::string Ticket::getdiemDi()
{
    return this->diemDi;
}

void Ticket::setdiemDi(std::string diemDi)
{
    this->diemDi = diemDi;
}

std::string Ticket::getdiemDen()
{
    return this->diemDen;
}

void Ticket::setdiemDen(std::string diemDen)
{
    this->diemDen = diemDen;
}

void Ticket::setloaiVe(std::string loaiVe)
{
    this->loaiVe = loaiVe;
}

std::string Ticket::getloaiVe()
{
    return this->loaiVe;
}

std::string Ticket::getngayKhoiHanh()
{
    return this->ngayKhoiHanh;
}

void Ticket::setngayKhoiHanh(std::string ngayKhoiHanh)
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
