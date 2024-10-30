#ifndef CLASS_H
#define CLASS_H
#include <iostream>
#include "Graph.h"
#include "LinkedList.h"

using namespace std;

class ChuyenBay {
private:
    string ID_chuyenBay;
    string ID_mayBay;
    string ngayKhoiHanh;
    string thoiLuongBay;
    string diemDi;
    string diemDen;

protected:
    LinkedList<Airport> duongBay;  
    void chinhSuaThongTin();// Protected: Chỉ có quản lý mới cần chỉnh sửa thông tin

public:
    void capNhatChoNgoi();  
};

class MayBay {
private:
    string ID_mayBay;
    string loaiMayBay;
    int soGhe;

public:
    void themGhe();      
    void xoaGhe();       
    unsigned int capNhatGhe(); 
};

class Ve {
private:
    string ID_chuyenBay;
    string loaiVe;
    int soGhe;
    float giaVe;

public:
    void kiemTraTrangThai();  
    void capNhatTrangThai(); 
};

class veThuongGia : public Ve {
public:
    void tienIch();  
};

class vePhoThong : public Ve {
public:
    void giaRe();   
};

class ThongTinVe {
private:
    string ID_ve;
    string ID_khachHang;
    string ngayXuatVe;
    string ngayKhoiHanh;

public:
    void hienThiThongTinVe(); 
};

class Payment {
private:
    string ID_thanhToan;
    string phuongThucThanhToan;
    float soTienThanhToan;
    string status;
    string thoiGianThanhToan;
    string ngayThanhToan;
    string hoanVe;

public:
    void kiemTraThanhToan();  
    void hoanVe();           
};

#endif