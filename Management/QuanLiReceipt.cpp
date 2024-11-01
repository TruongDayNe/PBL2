#include "QuanLiReceipt.h"

std::string lineReceiptFormat(std::string key, std::string info)
{
    std::string s = key;
    int n = 57 - key.length() - info.length();
    for (int i = 0; i < n; i++)
    {
        s += " ";
    }
    s = s + info;
    s = "|   " + s + "   |";
    return s;
}

std::string lineReceiptFormat(std::string qty, std::string item, std::string amount)
{
    std::string s = qty;
    int n = 6 - qty.length();
    for (int i = 0; i < n; i++)
    {
        s += " ";
    }
    s = s + item;
    int m = 57 - s.length() - amount.length();
    for (int i = 0; i < m; i++)
    {
        s += " ";
    }
    s = s + amount;
    s = "|   " + s + "   |";
    return s;
}

void printReceipt(int KhachHangID, std::string recID)
{
    std::ifstream inFile("./Page/Receipt.txt");
    std::ifstream inFileRec("./Database/ReceiptDB/" + std::to_string(KhachHangID) + "_" + recID + ".txt");

    std::string line;
    std::string lineRec;
    int firstIndex;

    for (int i = 0; i < 9; i++)
    {
        getline(inFile, line);
        std::cout << line << std::endl;
    }

    std::cout << lineReceiptFormat("No.", recID) << std::endl;

    getline(inFileRec, lineRec);
    std::cout << lineReceiptFormat("Issue Date", lineRec) << std::endl;
    getline(inFileRec, lineRec);
    int total = stoi(lineRec);

    for (int i = 0; i < 3; i++)
    {
        getline(inFile, line);
        std::cout << line << std::endl;
    }

    int quantity, ID_ve, amount;
    while (getline(inFileRec, lineRec))
    {
        firstIndex = lineRec.find_first_of(" ");
        quantity = stoi(lineRec.substr(0, firstIndex));
        ID_ve = stoi(lineRec.substr(firstIndex + 1));
        Ticket ve = getTicketFromDatabase(ID_ve);
        amount = quantity * ve.getgiaVe();
        std::cout << lineReceiptFormat(std::to_string(quantity), ve.getID_chuyenBay(), formatCurrency(amount)) << std::endl;
    }

    for (int i = 0; i < 1; i++)
    {
        getline(inFile, line);
        std::cout << line << std::endl;
    }

    std::cout << lineReceiptFormat("TOTAL AMOUNT", formatCurrency(total)) << std::endl;

    while (getline(inFile, line))
    {
        std::cout << line << std::endl;
    }

    inFileRec.close();
    inFile.close();
}

bool isValidReceiptID(std::string recID, KhachHang &KhachHang)
{
    LinkedList<std::string> recs = KhachHang.Rec();

    for (int i = 0; i < recs.length(); i++)
    {
        if (recs.get(i) == recID)
        {
            return true;
        }
    }
    return false;
}

void getReceiptFromDatabase(int KhachHangID, int recID)
{
    std::ifstream inFile("./Page/Receipt.txt");
    std::ifstream inFileRec("./Database/ReceiptDB/" + std::to_string(KhachHangID) + "_" + std::to_string(recID) + ".txt");

    std::string line;
    std::string lineRec;
    int firstIndex;

    for (int i = 0; i < 9; i++)
    {
        getline(inFile, line);
        std::cout << line << std::endl;
    }

    std::cout << lineReceiptFormat("No.", std::to_string(recID)) << std::endl;

    getline(inFileRec, lineRec);
    std::cout << lineReceiptFormat("Terminal.", lineRec) << std::endl;
    getline(inFileRec, lineRec);
    int total = stoi(lineRec);

    for (int i = 0; i < 3; i++)
    {
        getline(inFile, line);
        std::cout << line << std::endl;
    }

    int quantity, ID_ve, amount;
    while (getline(inFileRec, lineRec))
    {
        firstIndex = lineRec.find_first_of(" ");
        quantity = stoi(lineRec.substr(0, firstIndex));
        ID_ve = stoi(lineRec.substr(firstIndex + 1));
        Ticket ve = getTicketFromDatabase(ID_ve);
        amount = quantity * ve.getgiaVe();
        std::cout << lineReceiptFormat(std::to_string(quantity), ve.getID_chuyenBay(), formatCurrency(amount)) << std::endl;
    }

    for (int i = 0; i < 1; i++)
    {
        getline(inFile, line);
        std::cout << line << std::endl;
    }

    std::cout << lineReceiptFormat("TOTAL AMOUNT", formatCurrency(total)) << std::endl;

    while (getline(inFile, line))
    {
        std::cout << line << std::endl;
    }

    inFileRec.close();
    inFile.close();
}

void getAllKhachHangReceipts(KhachHang &KhachHang)
{
    TextTable table;
    int n = KhachHang.Rec().length();
    table.add("ID");
    table.add("Name");
    table.add("Receipt ID");
    table.add("Total");
    table.add("Datetime");
    table.endOfRow();

    int total = 0;
    for (int i = 0; i < n; i++)
    {
        table.add(std::to_string(KhachHang.getID()));
        table.add(KhachHang.getName());
        table.add(KhachHang.Rec().get(i));
        table.add(formatCurrency(getReceiptTotal(KhachHang.getID(), KhachHang.Rec().get(i))));
        table.add(getReceiptDateTime(KhachHang.getID(), KhachHang.Rec().get(i)));
        table.endOfRow();
        total += getReceiptTotal(KhachHang.getID(), KhachHang.Rec().get(i));
    }
    table.add("");
    table.add("");
    table.add("Total amount");
    table.add(formatCurrency(total));
    table.add("");
    table.endOfRow();

    std::cout << table << std::endl;
}

void addReceiptToDatabase(int KhachHangID, Cart _Cart, LinkedList<std::string> Rec)
{
    std::string recID = "REC#" + std::to_string(Rec.length() + 1);
    Rec.addLast(recID);

    std::string fileName = std::to_string(KhachHangID) + "_" + recID + ".txt";
    std::string filePath = "./Database/ReceiptDB/" + fileName;
    std::ofstream outFileKhachHang("./Database/UserDB/KhachHangDB/KhachHang_" + std::to_string(KhachHangID) + ".txt", std::ios::app);
    outFileKhachHang << recID << std::endl;
    outFileKhachHang.close();

    std::ofstream outFile(filePath);

    std::string date = currentDateTime();
    outFile << date << std::endl;
    outFile << _Cart.Total() <<std:: endl;

    for (int i = 0; i < _Cart.ID_veMua().length(); i++)
    {
        outFile << _Cart.soVeMua().get(i) << " ";
        outFile << _Cart.ID_veMua().get(i) << std::endl;
    }

    outFile.close();
    system("cls");
    printReceipt(KhachHangID, recID);

    // _Cart.emptyCart();
}

void deleteReceiptFromDatabase(int KhachHangID, std::string recID)
{
    std::string fileName = std::to_string(KhachHangID) + "_" + recID + ".txt";
    std::string filePath = "./Database/ReceiptDB/" + fileName;

    char char_filePath[(filePath + fileName).length() + 1];
    strcpy(char_filePath, (filePath + fileName).c_str());

    int status = remove(char_filePath);

    if (status == 0)
    {
        printSuccess("Succesfully delete this Receipt!");
    }
    else
    {
        printError("Delete failed!");
    }
}