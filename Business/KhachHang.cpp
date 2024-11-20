#include "KhachHang.h"

KhachHang::KhachHang() : User(0, "", "", "")
{
    this->_Rec = LinkedList<std::string>();
    this->_Cart = Cart();
}

KhachHang::KhachHang(int id, std::string name, std::string email, std::string password, LinkedList<std::string> recs) : User(id, name, email, password)
{
    this->_Rec = recs;
    this->_Cart = Cart();
}

KhachHang::~KhachHang()
{
}

KhachHang& KhachHang::operator=(const KhachHang& other) {
    if (this != &other) {
        // Gán các thành viên từ lớp cơ sở (User)
        User::operator=(other);

        // Gán các thành viên của KhachHang
        this->_Cart = other._Cart;
        this->_Rec = other._Rec;  // Giả sử LinkedList có toán tử gán
    }
    return *this;
}

Cart &KhachHang::getCart()
{
    return this->_Cart;
}

LinkedList<std::string> KhachHang::Rec()
{
    return this->_Rec;
}

void KhachHang::setRec(LinkedList<std::string> recs)
{
    this->_Rec = recs;
}

void KhachHang::purchase()
{
    std::string recID = "REC#" + std::to_string(this->_Rec.length() + 1);
    this->_Rec.addLast(recID);

    std::string fileName = std::to_string(this->getID()) + "_" + recID + ".txt";
    std::string filePath = "./Database/ReceiptDB/" + fileName;
    std::ofstream outFileKhachHang("./Database/UserDB/KhachHangDB/KhachHang_" + std::to_string(this->getID()) + ".txt", std::ios::app);
    outFileKhachHang << recID << std::endl;
    outFileKhachHang.close();

    std::ofstream outFile(filePath);

    std::string date = currentDateTime();
    outFile << date <<std::endl;
    outFile << _Cart.Total() << std::endl;

    for (int i = 0; i < _Cart.ID_veMua().length(); i++)
    {
        outFile << _Cart.soVeMua().get(i) << " ";
        outFile << _Cart.ID_veMua().get(i) << std::endl;
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

void KhachHang::deleteReceiptById(std::string id)
{
    deleteReceiptFromDatabase(this->getID(), id);
}
