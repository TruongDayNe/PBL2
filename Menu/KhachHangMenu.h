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

class KhachHang;
class KhachHangMenu
{
public:
    static int printTask();                    // In ra console các chức năng
    static void purchaseTicket(KhachHang &);       // Mua bán thuốc
    static void searchTicket(KhachHang &);         // Tìm kiếm thông tin thuốc
    static void orderTicketHistory(KhachHang &);   // Lịch sử mua bán thuốc
    // static void bookAppointment(Patient &);    // Đặt lịch hẹn
    // static void viewMedicalHistory(Patient &); // Xem lịch sử khám
    static void menu(KhachHang &);               // Thực hiện các chức năng menu, switchcase
    static void login();
    static void signUp();
    static void KH_main();
};