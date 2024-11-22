#pragma once

#ifndef KHACHHANG_H
#define KHACHHANG_H
#include "User.h"
#include <iostream>
#include "Cart.h"
#include "../Management/QuanLiVe.h"

class KhachHang : public User{
    private:
        Cart _Cart;
        LinkedList<Ticket> _Rec;
    public:
        // Constructor
    KhachHang();
    KhachHang(int, std::string, std::string, std::string,std::string, std::string, LinkedList<Ticket> = LinkedList<Ticket>());

    // Destructor
    ~KhachHang();

    KhachHang& operator=(const KhachHang& other);

    // Info
    void displayInfo();
    void updateInfo();

    // Get KhachHang item in Cart
    Cart &getCart();

    // Get list of ticket
    LinkedList<Ticket> Rec();

    // Set list of receipt ID
    void setRec(LinkedList<Ticket>);

    void newKhachHang();

    void purchase();
    void searchByTicketID(std::string);
    // void searchByCompName(std::string);
    void printAllKhachHangPurchases();
    // void printReceipt(int);
    void addNewReceipt();
    void deleteTicketById(std::string);
 
};
#endif