#pragma once
#include "User.h"
#include "Cart.h"
#include "LinkedList.h"

class KhachHang : public User {
    private:
        Cart _Cart;
        LinkedList<string> _Rec;
    public:
        // Constructor
    KhachHang();
    KhachHang(int, string, string, string, LinkedList<string> = LinkedList<string>());

    // Destructor
    ~KhachHang();

    // Info
    void displayInfo();
    void updateInfo();

    // Get KhachHang item in Cart
    Cart &getCart();

    // Get list of receipt ID
    LinkedList<string> Rec();

    // Set list of receipt ID
    void setRec(LinkedList<string>);

    void newKhachHang();

    void purchase();
    void searchByReceiptID(int);
    // void searchByCompName(string);
    void printAllKhachHangReceipts();
    // void printReceipt(int);
    void addNewReceipt();
    void deleteReceiptById(string);
 
};