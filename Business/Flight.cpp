#include "Flight.h"

Flight::Flight()
{
    this->ID_chuyenBay = " ";
    this->diemDi = " ";
    this->diemDen = " ";
    this->ngayKhoiHanh = "";
    this->soLuongVe = 0;
    this->giaVe = 0;
}

Flight::Flight(std::string ID_chuyenBay, std::string diemDi, std::string diemDen, std::string ngayKhoiHanh, int soLuongVe, int giaVe)
{
    this->ID_chuyenBay = ID_chuyenBay;
    this->diemDi = diemDi;
    this->diemDen = diemDen;
    this->ngayKhoiHanh = ngayKhoiHanh;
    this->soLuongVe = soLuongVe;
    this->giaVe = giaVe;
    // Khởi tạo danh sách vé
    for (int i = 0; i < soLuongVe; i++) 
    {
        std::string ticketID = ID_chuyenBay + "_" + to_string(i + 1);
        std::string ghe = "Ghe_" + to_string(i + 1);
        KhachHang khachHang;
        tickets.addLast(Ticket(ticketID, *this, khachHang, ghe, giaVe));
    }
}

Flight::Flight(const Flight& chuyenBay)
{
    this->ID_chuyenBay = chuyenBay.ID_chuyenBay;
    this->diemDi = chuyenBay.diemDi;
    this->diemDen = chuyenBay.diemDen;
    this->ngayKhoiHanh = chuyenBay.ngayKhoiHanh;
    this->soLuongVe = chuyenBay.soLuongVe;
    this->giaVe = chuyenBay.giaVe;
}

Flight& Flight::operator = (const Flight& chuyenBay)
{
    this->ID_chuyenBay = chuyenBay.ID_chuyenBay;
    this->diemDi = chuyenBay.diemDi;
    this->diemDen = chuyenBay.diemDen;
    this->ngayKhoiHanh = chuyenBay.ngayKhoiHanh;
    this->soLuongVe = chuyenBay.soLuongVe;
    this->giaVe = chuyenBay.giaVe;
    return *this;
}

Flight::~Flight()
{
}

std::string Flight::getID_chuyenBay()
{
    return this->ID_chuyenBay;
}

void Flight::setID_chuyenBay(std::string ID_chuyenBay)
{
    this->ID_chuyenBay = ID_chuyenBay;
}

std::string Flight::getdiemDi()
{
    return this->diemDi;
}

void Flight::setdiemDi(std::string diemDi)
{
    this->diemDi = diemDi;
}

std::string Flight::getdiemDen()
{
    return this->diemDen;
}

void Flight::setdiemDen(std::string diemDen)
{
    this->diemDen = diemDen;
}

std::string Flight::getngayKhoiHanh()
{
    return this->ngayKhoiHanh;
}

void Flight::setngayKhoiHanh(std::string ngayKhoiHanh)
{
    this->ngayKhoiHanh = ngayKhoiHanh;
}

int Flight::getsoLuongVe()
{
    return this->soLuongVe;
}

void Flight::setsoLuongVe(int soLuongVe)
{
    this->soLuongVe = soLuongVe;
}

int Flight::getgiaVe()
{
    return this->giaVe;
}

void Flight::setgiaVe(int giaVe)
{
    this->giaVe = giaVe;
}
