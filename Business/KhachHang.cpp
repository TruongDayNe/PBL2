#include "KhachHang.h"
#include "Cart.h"

KhachHang::KhachHang() : User(0, "", "", "")
{
    this->_Rec = LinkedList<std::string>();
    this->_Cart = Cart();
}

KhachHang::KhachHang(int id, std::string name, std::string email, std::string password,std::string cccd , std::string phone, LinkedList<std::string> recs) : User(id, name, email, password, cccd, phone)
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

// Khi lựa xong vé sẽ mua, điền thông tin từng người sở hữu vé
void KhachHang::purchase()
{
    std::string recID = "Purchased_" + std::to_string(this->getCart().veMua().length());
    //Hóa đơn được lưu ở ReceiptDB

    std::string fileName = std::to_string(this->getID()) + "_" + recID + ".txt";
    std::string filePath = "./Database/ReceiptDB/" + fileName;

    //ghi vào file thông tin khách hàng 
    std::ofstream outFileKhachHang("./Database/UserDB/KhachHangDB/KhachHang_" + std::to_string(this->getID()) + ".txt", std::ios::app);
    outFileKhachHang << fileName << std::endl;
    outFileKhachHang.close();

    std::ofstream outFile(filePath);

    //thông tin giao dịch lưu trong ReiceitDB
    std::string date = currentDateTime();
    outFile << date <<std::endl;
    outFile << _Cart.Total() << std::endl;
    //in ra tất cả các vé
    for (int i = 0; i < _Cart.veMua().length(); i++)
    {
        outFile << _Cart.veMua().get(i).getID_ve() << std::endl;
    }

    outFile.close();
    system("cls");
    for (int i = 0; i < _Cart.veMua().length(); i++)
    {
        printTicket(this->getID(), _Cart.veMua().get(i));
    }

    system("pause");

    _Cart.emptyCart();
}

void KhachHang::searchByTicketID(std::string id)
{
    getTicketFromDatabase(this->getID(), findTicketById(id));
}

void KhachHang::printAllKhachHangPurchases()
{
    getAllKhachHangTickets(*this);
}

// void KhachHang::addNewReceipt()
// {
//     addTicketToDatabase(this->getID(), this->_Cart, this->_Rec);
// }

void KhachHang::deleteTicketById(std::string id)
{
    deleteTicketFromDatabase(this->getID(), id);
}
