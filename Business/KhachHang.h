#pragma once

#include "User.h"
//#include "Cart.h"
#include "../Management/QuanLiVe.h"
#include "../Management/QuanLiReceipt.h"
#include <iostream>

#ifndef KHACHHANG_H
#define KHACHHANG_H

class KhachHang : public User {
    private:
        //Cart _Cart;
        LinkedList<std::string> _Rec;
    public:
        // Constructor
    KhachHang();
    KhachHang(int, std::string, std::string, std::string, LinkedList<std::string> = LinkedList<std::string>());

    // Destructor
    ~KhachHang();

    // Info
    void displayInfo();
    void updateInfo();

    // Get KhachHang item in Cart
    //Cart &getCart();

    // Get list of receipt ID
    LinkedList<std::string> Rec();

    // Set list of receipt ID
    void setRec(LinkedList<std::string>);

    void newKhachHang();

    void purchase();
    void searchByReceiptID(int);
    // void searchByCompName(std::string);
    void printAllKhachHangReceipts();
    // void printReceipt(int);
    void addNewReceipt();
    void deleteReceiptById(std::string);
 
};
#endif