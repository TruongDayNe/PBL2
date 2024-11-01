#pragma once
#include <iostream>
#include <fstream>
#include "D:/Code/PBL2/Library/Console.h"
#include "D:/Code/PBL2/Business/KhachHang.h"
#include "D:/Code/PBL2/Library/MenuBox.h"
#include "D:/Code/PBL2/Management/QuanLiKhachHang.h"
#include "D:/Code/PBL2/Management/QuanLiVe.h"
#include "D:/Code/PBL2/Management/QuanLiNguoiDung.h"
#include "D:/Code/PBL2/Management/QuanLiReceipt.h"
#include "D:/Code/PBL2/Library/Table.cpp"
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