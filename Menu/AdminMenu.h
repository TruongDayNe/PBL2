#pragma once
#include <iostream>
#include <fstream>
#include "../Library/Console.h"
#include "../Business/KhachHang.h"
#include "../Library/MenuBox.h"
#include "../Management/QuanLiKhachHang.h"
#include "../Management/QuanLiChuyenBay.h"
#include "../Management/QuanLiNguoiDung.h"
#include "../Management/QuanLiVe.h"
#include "../Library/Table.cpp"
#include <string>
#include "Home.h"

// #include "QuanLiChuyenBay.h"
class Admin;
class AdminMenu
{
public:
    static int printTask();
    static void menu(Admin &);                      // In ra console các chức năng
    // static void searchDrug(Doctor &);            // Tìm kiếm thông tin thuốc
    // static void drugManagement(Doctor &);        // Xem, thêm, cập nhật, xóa,...
    // static void searchPatient(Doctor &);         // Tìm theo tên, ID
    // static void patientManagement(Doctor &);     // Thêm, xóa, cập nhật, tìm kiếm
    // static void appointmentManagement(Doctor &); // Xem lịch tổng quát, xem ngày chi tiết, thống kê doanh thu trong tháng
    // static void saleDrugManagement(Doctor &);    // Lịch sử mua bán thuốc
    // static void menu(Doctor &);                  // Thực hiện các chức năng menu, switchcase
    static void login();
    static void AD_main();
};