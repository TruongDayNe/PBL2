#pragma once

#ifndef KHACHHANG_H
#define KHACHHANG_H
#include "User.h"
#include <iostream>
#include "Cart.h"
#include "../Management/QuanLiVe.h"
#include "../Menu/KhachHangMenu.h"

class KhachHang : public User{
    private:
        Cart _Cart;
        LinkedList<std::string> _Rec;
    public:
        // Constructor
    KhachHang();
    KhachHang(int, std::string, std::string, std::string,std::string, std::string, LinkedList<std::string> = LinkedList<std::string>());

    // Destructor
    ~KhachHang();

    KhachHang& operator=(const KhachHang& other);

    // Info
    void displayInfo();
    void updateInfo();

    // Get KhachHang item in Cart
    Cart &getCart();

    // Get list of ticket
    LinkedList<std::string> Rec();

    // Set list of receipt ID
    void setRec(LinkedList<std::string>);

    void newKhachHang();

    void purchase(LinkedList<int>);
    void searchByTicketID(std::string);
    // void searchByCompName(std::string);
    void printAllKhachHangPurchases();
    // void printReceipt(int);
    void addNewReceipt();
    void deleteTicketById(std::string);
 
};
#endif