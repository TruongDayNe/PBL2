#include "QuanLiVe.h"


std::string lineTicketFormat(std::string key, std::string info)
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

std::string lineTicketFormat(std::string qty, std::string item, std::string amount)
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

void printTicket(int KhachHangID, Ticket ticket)
{
    std::ifstream inFile("./Page/Ticket.txt");
    //std::ifstream inFileRec("./Database/TicketDB/" + std::to_string(KhachHangID) + "_" + ticket.getID_ve() + ".txt");

    std::string line;
    std::string lineRec;
    int firstIndex;

    //in tới hàng 5
    for (int i = 0; i < 5; i++)
    {
        getline(inFile, line);
        std::cout << line << std::endl;
    }

    std::cout << lineTicketFormat("Departure", ticket.getChuyenBay().getdiemDi()) << std::endl;
    std::cout << lineTicketFormat("Arrival", ticket.getChuyenBay().getdiemDen()) << std::endl;

    //in tới hàng 8
    for (int i = 5; i < 8; i++)
    {
        getline(inFile, line);
        std::cout << line << std::endl;
    }

    //getline(inFileRec, lineRec);
    std::cout << lineTicketFormat("Issue Date", currentDateTime()) << std::endl;
    //getline(inFileRec, lineRec);

    //in tới dòng 10
    for (int i = 8; i < 10; i++)
    {
        getline(inFile, line);
        std::cout << line << std::endl;
    }

    // in thông tin vé theoo database từng dòng
    // int quantity, ID_ve, amount;
    // while (getline(inFileRec, lineRec))
    // {
    //     firstIndex = lineRec.find_first_of(" ");
    //     quantity = std::stoi(lineRec.substr(0, firstIndex));
    //     ID_ve = std::stoi(lineRec.substr(firstIndex + 1));
    //     Ticket ve = getTicketFromDatabase(ID_ve);
    //     amount = quantity * ve.getgiaVe();
    //     std::cout << lineTicketFormat(std::to_string(quantity), ve.getChuyenBay().getID_chuyenBay(), formatCurrency(amount)) << std::endl;
    // }

    //in thông tin vé từ đối tương ticket
    std::cout << lineTicketFormat(ticket.getChuyenBay().getID_chuyenBay(), ticket.getChuyenBay().getngayKhoiHanh() , ticket.getGhe()) << std::endl;

    for (int i = 0; i < 1; i++)
    {
        getline(inFile, line);
        std::cout << line << std::endl;
    }

    // std::cout << lineTicketFormat("TOTAL AMOUNT", formatCurrency(total)) << std::endl;

    while (getline(inFile, line))
    {
        std::cout << line << std::endl;
    }

    //inFileRec.close();
    inFile.close();
}

// bool isValidTicketID(std::string ticketID, KhachHang &KhachHang)
// {
//     LinkedList<Ticket> tickets = KhachHang.Rec();

//     for (int i = 0; i < tickets.length(); i++) {
//         if (tickets.get(i).getID_ve() == ticketID) {
//             return true;
//         }
//     }
//     return false;
// }

bool isValidTicketID(std::string ticketID) 
{
    LinkedList<Flight> flights = getAllFlight();

    for (int i = 0; i < flights.length(); i++) {
        for (int j = 0; j < flights.get(i).tickets.length(); j++) {
            if (flights.get(i).tickets.get(j).getID_ve() == ticketID) {
                return true;
            }
        }
    }
    return false;
}

//in ra v
void getTicketFromDatabase(int KhachHangID, Ticket ticket)
{
    std::ifstream inFile("./Page/Receipt.txt");
    std::ifstream inFileRec("./Database/ReceiptDB/" + std::to_string(KhachHangID) + "_" + ticket.getID_ve() + ".txt");

    std::string line;
    std::string lineRec;
    int firstIndex;

    //in tới hàng 5
    for (int i = 0; i < 5; i++)
    {
        getline(inFile, line);
        std::cout << line << std::endl;
    }

    std::cout << lineTicketFormat("Departure", ticket.getChuyenBay().getdiemDi()) << std::endl;
    std::cout << lineTicketFormat("Arrival", ticket.getChuyenBay().getdiemDen()) << std::endl;

    //in tới hàng 8
    for (int i = 5; i < 8; i++)
    {
        getline(inFile, line);
        std::cout << line << std::endl;
    }

    getline(inFileRec, lineRec);
    std::cout << lineTicketFormat("Issue Date", lineRec) << std::endl;
    getline(inFileRec, lineRec);
    int total = std::stoi(lineRec);

    //in tới dòng 10
    for (int i = 8; i < 10; i++)
    {
        getline(inFile, line);
        std::cout << line << std::endl;
    }

    // in thông tin vé theoo database từng dòng
    // int quantity, ID_ve, amount;
    // while (getline(inFileRec, lineRec))
    // {
    //     firstIndex = lineRec.find_first_of(" ");
    //     quantity = std::stoi(lineRec.substr(0, firstIndex));
    //     ID_ve = std::stoi(lineRec.substr(firstIndex + 1));
    //     Ticket ve = getTicketFromDatabase(ID_ve);
    //     amount = quantity * ve.getgiaVe();
    //     std::cout << lineTicketFormat(std::to_string(quantity), ve.getChuyenBay().getID_chuyenBay(), formatCurrency(amount)) << std::endl;
    // }

    //in thông tin vé từ đối tương ticket
    std::cout << lineTicketFormat(ticket.getChuyenBay().getID_chuyenBay(), ticket.getChuyenBay().getngayKhoiHanh() , ticket.getGhe()) << std::endl;

    for (int i = 0; i < 1; i++)
    {
        getline(inFile, line);
        std::cout << line << std::endl;
    }

    // std::cout << lineTicketFormat("TOTAL AMOUNT", formatCurrency(total)) << std::endl;

    while (getline(inFile, line))
    {
        std::cout << line << std::endl;
    }

    inFileRec.close();
    inFile.close();
}

void getAllKhachHangTickets(KhachHang &KhachHang)
{
    TextTable table;
    int n = KhachHang.Rec().length();
    table.add("Ticket ID");
    table.add("Passenger");
    table.add("Date of departure");
    table.add("Price");
    table.endOfRow();

    int total = 0;
    for (int i = 0; i < n; i++)
    {
        LinkedList<Ticket> KhachHangReceipts = getTicketFromReceipt(KhachHang.Rec().get(i));
        for (int j = 0; j < KhachHangReceipts.length(); j++)
        {
            Ticket KhachHangTicket = KhachHangReceipts.get(j);
            table.add(KhachHangTicket.getID_ve());
            table.add(KhachHangTicket.getKhachHang().getName());
            table.add(KhachHangTicket.getChuyenBay().getngayKhoiHanh());
            table.add(formatCurrency(KhachHangTicket.getgiaVe()));
            table.endOfRow();
            total += KhachHangTicket.getgiaVe();
        }
    }
    table.add("");
    table.add("");
    table.add("Total amount");
    table.add(formatCurrency(total));
    table.endOfRow();

    std::cout << table << std::endl;
}

void addTicketToDatabase(int KhachHangID, Cart _Cart, LinkedList<std::string> Rec)
{
    std::string ticketID = "Ticket#" + std::to_string(Rec.length() + 1);
    Ticket ticket;
    ticket.setID_ve(ticketID);
    Rec.addLast(ticketID);

    std::string fileName = std::to_string(KhachHangID) + "_" + ticketID + ".txt";
    std::string filePath = "./Database/ReceiptDB/" + fileName;
    std::ofstream outFileKhachHang("./Database/UserDB/KhachHangDB/KhachHang_" + std::to_string(KhachHangID) + ".txt", std::ios::app);
    outFileKhachHang << ticketID << std::endl;
    outFileKhachHang.close();

    std::ofstream outFile(filePath);

    std::string date = currentDateTime();
    outFile << date << std::endl;
    outFile << _Cart.Total() <<std:: endl;

    for (int i = 0; i < _Cart.veMua().length(); i++)
    {
        outFile << _Cart.soVeMua().get(i) << " ";
        outFile << _Cart.veMua().get(i).getID_ve() << std::endl;
    }

    outFile.close();
    system("cls");
    printTicket(KhachHangID, ticket);

    // _Cart.emptyCart();
}

//fix lại
void deleteTicketFromDatabase(int KhachHangID, std::string recID)
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

Ticket findTicketById(const std::string& ticketID) 
{
    LinkedList<Flight> flights = getAllFlight();

    for (int i = 0; i < flights.length(); i++) 
    {
        for (int j = 0; j < flights.get(i).tickets.length(); j++) {
            if (flights.get(i).tickets.get(j).getID_ve() == ticketID) 
            {
                // Tìm thấy vé, trả về địa chỉ của nó
                return flights.get(i).tickets.get(j);
            }
        }
    }
    throw std::runtime_error("Không tìm thấy vé với ID: " + ticketID);
}

LinkedList<Ticket> getTicketFromReceipt(std::string recID)
{
    std::ifstream inFile("./Database/ReceiptDB/" + recID + ".txt");
    std::string line;
    int firstIndex;
    LinkedList<Ticket> tickets;

    getline(inFile, line);
    getline(inFile, line);
    while (getline(inFile, line))
    {
        // firstIndex = line.find_first_of(" ");
        // std::string ID_ve = line.substr(firstIndex);
        Ticket ve = findTicketById(line);
        tickets.addLast(ve);
    }

    inFile.close();
    return tickets;
}