#include "KhachHang.h"
#include "Ticket.cpp"
#include "../Management/QuanLiVe.cpp"
#include "../Management/QuanLiReceipt.cpp"
#include <iostream>
using namespace std;

KhachHang::KhachHang() : User(0, "", "", "")
{
    this->_Rec = LinkedList<string>();
    this->_Cart = Cart();
}

KhachHang::KhachHang(int id, string name, string email, string password, LinkedList<string> recs) : User(id, name, email, password)
{
    this->_Rec = recs;
    this->_Cart = Cart();
}

KhachHang::~KhachHang()
{
}

Cart &KhachHang::getCart()
{
    return this->_Cart;
}

LinkedList<string> KhachHang::Rec()
{
    return this->_Rec;
}

void KhachHang::setRec(LinkedList<string> recs)
{
    this->_Rec = recs;
}

void KhachHang::purchase()
{
    string recID = "REC#" + to_string(this->_Rec.length() + 1);
    this->_Rec.addLast(recID);

    string fileName = to_string(this->getID()) + "_" + recID + ".txt";
    string filePath = "./Database/ReceiptDB/" + fileName;
    ofstream outFileKhachHang("./Database/UserDB/KhachHangDB/CUSTOMER_" + to_string(this->getID()) + ".txt", ios::app);
    outFileKhachHang << recID << endl;
    outFileKhachHang.close();

    ofstream outFile(filePath);

    string date = currentDateTime();
    outFile << date << endl;
    outFile << _Cart.Total() << endl;

    for (int i = 0; i < _Cart.ID_veMua().length(); i++)
    {
        outFile << _Cart.soVeMua().get(i) << " ";
        outFile << _Cart.ID_veMua().get(i) << endl;
    }

    outFile.close();
    system("cls");
    printReceipt(this->getID(), recID);

    _Cart.emptyCart();
}

void KhachHang::searchByReceiptID(int id)
{
    getReceiptFromDatabase(this->getID(), id);
}

void KhachHang::printAllKhachHangReceipts()
{
    getAllKhachHangReceipts(*this);
}

void KhachHang::addNewReceipt()
{
    addReceiptToDatabase(this->getID(), this->_Cart, this->_Rec);
}

void KhachHang::deleteReceiptById(string id)
{
    deleteReceiptFromDatabase(this->getID(), id);
}
