#pragma once
#include <iostream>
#include <fstream>
#include "../Library/Console.h"
#include "../Business/KhachHang.h"
#include "../Library/MenuBox.h"
#include "../Management/QuanLiKhachHang.h"
#include "../Management/QuanLiVe.h"
#include "../Management/QuanLiNguoiDung.h"
#include "../Management/QuanLiReceipt.h"
#include "../Library/Table.cpp"
#include <string>
#include "Home.h"

class KhachHang;
class KhachHangMenu
{
public:
    static int printTask();                    // In ra console các chức năng
    static void purchaseTicket(KhachHang &khachHang, LinkedList<Ticket> tickets = getAllTicket());       // Mua bán thuốc
    static void searchTicket(KhachHang &);         // Tìm kiếm thông tin thuốc
    static void orderTicketHistory(KhachHang &);   // Lịch sử mua bán thuốc
    // static void bookAppointment(Patient &);    // Đặt lịch hẹn
    // static void viewMedicalHistory(Patient &); // Xem lịch sử khám
    static void menu(KhachHang &);               // Thực hiện các chức năng menu, switchcase
    static void login();
    static void signUp();
    static void KH_main();
};