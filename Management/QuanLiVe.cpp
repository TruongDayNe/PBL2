#include "QuanLiVe.h"

// bool isValidTicketId(int ticketID)
// {
//     std::ifstream inFile("./Database/TicketDB/ticket_ID.txt");
//     std::string x;
//     while (getline(inFile, x))
//     {
//         if (std::stoi(x) == ticketID)
//         {
//             return true;
//         }
//     }
//     inFile.close();
//     return false;
// }

bool isValidTicketId( const std::string& flightId){
    std:: ifstream inFile("PBL2/Database/lastID.txt");
    if(!inFile.is_open()){
        std::cout<<"Can not open the file!"<<std::endl;
        return false;
    }
    std::string line;

    while(getline(inFile, line)){
        // Loại bỏ khoảng trắng thừa ở đầu và cuối nếu có
        line.erase(0, line.find_first_not_of(" "));
        line.erase(line.find_last_not_of(" ") + 1);

        if(line== flightId){
            inFile.close();
            return true;

        }
    }
}

void addTicketToDatabase(Ticket &ticket)
{
    // generate file path
    // start from main.cpp
    // std::string fileName = std::to_string(ticket.getID_ve()) + ".txt";
    // std::string filePath = "./Database/TicketDB/" + fileName;

    

    // create file in database
    std::fstream outFile("../TicketDB/ticket_ID.txt");
    int lastIndex = 0;
    if(outFile.is_open()){
        std::string line;
        while (std::getline(outFile, line)){
            lastIndex= std::stoi (line) ;
        }
    } else {
        std::cerr<< "Không thể mở tệp ticket_ID.txt" << std::endl;
        return;
    }

    outFile<<lastIndex<<" | "<<ticket.getID_chuyenBay() <<" | "<<ticket.getdiemDi()<<" | " << ticket.getdiemDen() <<" | "<<ticket.getloaiVe()<< " | "<<ticket.getngayKhoiHanh() <<" | "<<ticket.getsoLuongVe()<< " | "<< ticket.getgiaVe() << std::endl;

    if (!isValidTicketId(ticket.getID_chuyenBay()))
    {
        std::ofstream outFileTicketId("./Database/TicketDB/ticket_ID.txt", std::ios::app);
        outFileTicketId << ticket.getID_chuyenBay() << std::endl;
        outFileTicketId.close();
    }

    // close ofstream
    outFile.close();
}

void addNewTicketToDataBase()
{
    std::cout << spaceLineChoice + "New filght:\n";
    std::string ID_chuyenBay = getStringInput("ID chuyến bay");
    std::string loaiVe = getStringInput("Loại vé");
    std::string diemDi = getStringInput("Điểm đi");
    std::string diemDen = getStringInput("Điểm đến");
    std::string ngayKhoiHanh = getStringInput("Ngày giờ khởi hành (dd-mm-yy hh:mm:ss)");
    unsigned int soLuongVe = getIntInput("Số lượng vé");
    int giaVe = getIntInput("Giá vé");
    // Create new Ticket object
    Ticket ticket = Ticket( ID_chuyenBay, diemDi, diemDen, loaiVe, ngayKhoiHanh, soLuongVe, giaVe );

    // Save to database
    addTicketToDatabase(ticket);

    // Update new Ticket id range
    updateLine("./Database/lastID.txt", 0, ID_chuyenBay);

    // // Generate sale and write to sale file
    // ofstream outFilesale("./Database/saleSummary.txt", ios::app);
    // outFilesale << ticket.getID_ve() << " " << ticket.getsoGhe() << endl;
    // outFilesale.close();
}

Ticket getTicketFromDatabase(std::string ticketID)
{
    std::ifstream inFile("../TicketDB/ticket_ID.txt");
    if (!inFile.is_open()) {
        throw std::runtime_error("Không thể mở file");
    }

    std::string line;
    std::string soThuTu;
    std::string ID_chuyenBay;
    std::string diemDi;
    std::string diemDen;
    std::string loaiVe;
    std::string ngayKhoiHanh;
    std::string soLuongVe_str;
    std::string giaVe_str;
    
    bool found = false;
    while(getline(inFile, line)) {
        std::stringstream ss(line);
        getline(ss, soThuTu, '|');
        getline(ss, ID_chuyenBay, '|');
        getline(ss, diemDi, '|');
        getline(ss, diemDen, '|');
        getline(ss, loaiVe, '|');
        getline(ss, ngayKhoiHanh, '|');
        getline(ss, soLuongVe_str, '|');
        getline(ss, giaVe_str, '|');
        
        if (ID_chuyenBay == ticketID) {
            found = true;
            break;
        }
    }

    if (!found) {
        throw std::runtime_error("Không tìm thấy vé với ID này");
    }

    int soLuongVe = 0;
    int giaVe = 0;

    try {
        // Loại bỏ khoảng trắng và ký tự không mong muốn
        soLuongVe_str.erase(remove_if(soLuongVe_str.begin(), soLuongVe_str.end(), isspace), soLuongVe_str.end());
        giaVe_str.erase(remove_if(giaVe_str.begin(), giaVe_str.end(), isspace), giaVe_str.end());

        if (!soLuongVe_str.empty()) {
            soLuongVe = std::stoi(soLuongVe_str);
        }
        if (!giaVe_str.empty()) {
            giaVe = std::stoi(giaVe_str);
        }
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Lỗi chuyển đổi số: " + std::string(e.what()));
    }

    inFile.close();
    return Ticket(ID_chuyenBay, diemDi, diemDen, loaiVe, ngayKhoiHanh, soLuongVe, giaVe);
}
// Ticket getTicketFromDatabase(int ticketID)
// {
//     std::string fileName = std::to_string(ticketID) + ".txt";
//     std::string filePath = "./Database/TicketDB/" + fileName;

//     std::ifstream inFile(filePath);
//     std::string line;

//     std::string ID_chuyenBay;
//     std::string diemDi;
//     std::string diemDen;
//     std::string loaiVe;
//     std::string ngayKhoiHanh;
//     int soLuongVe=0;
//     int giaVe=0;


//     getline(inFile, line);
//     ticketID = std::stoi(line);

//     getline(inFile, line);
//     ID_chuyenBay = line;

//     getline(inFile, line);
//     diemDi = line;

//     getline(inFile, line);
//     diemDen = line;

//     getline(inFile, line);
//     loaiVe = line;

//     getline(inFile, line);
//     ngayKhoiHanh = line;

//     getline(inFile, line);
//     soLuongVe = std::stoi(line);

//     getline(inFile, line);
//     giaVe = std::stoi(line);

//     return  Ticket( ID_chuyenBay, diemDi, diemDen, loaiVe, ngayKhoiHanh, soLuongVe, giaVe);
// }
void deleteTicketFromDatabase(int ticketID)
{
    std::string filePath = "./Database/TicketDB/";
    std::string fileName = std::to_string(ticketID) + ".txt";

    // char char_filePath[(filePath + fileName).length() + 1];
    // strcpy(char_filePath, (filePath + fileName).c_str());

    int status = remove((filePath + fileName).c_str());

    if (status == 0)
    {
        printSuccess("Succesfully delete this Ticket!");
        eraseFileLine(filePath + "ticket_ID.txt", std::to_string(ticketID));
        //eraseFileLine("./Database/saleSummary.txt", ticketID);
    }
    else
    {
        printError("Delete failed!");
    }
}

void updateTicketInDatabase(std::string ticketID)
{
    Ticket ticket = getTicketFromDatabase(ticketID);
    std::string fileName = "../Database/TicketDB/ticket_ID.txt";

    int status = remove(fileName.c_str());

    std::string ID_chuyenBay = updateComponent("ID chuyến bay", ticket.getID_chuyenBay());
    std::string diemDi = updateComponent("Điểm đi", ticket.getdiemDi());
    std::string diemDen = updateComponent("Điểm đến", ticket.getdiemDen());
    std::string loaiVe = updateComponent("Loại vé", ticket.getloaiVe());
    std::string ngayKhoiHanh = updateComponent("Ngày khởi hành (dd-mm-yy hh:mm:ss)", ticket.getngayKhoiHanh());
    int soLuongVe = updateIntComponent("Số lượng vé", ticket.getsoLuongVe());
    int giaVe = updateIntComponent("Giá vé", ticket.getgiaVe());

    // ticket.setID_ve(ticketID);
    ticket.setID_chuyenBay(ID_chuyenBay);
    ticket.setdiemDi(diemDi);
    ticket.setdiemDen(diemDen);
    ticket.setloaiVe(loaiVe);
    ticket.setngayKhoiHanh(ngayKhoiHanh);
    ticket.setsoLuongVe(soLuongVe);
    ticket.setgiaVe(giaVe);

    addTicketToDatabase(ticket);
    printSuccess("Succesfully update!");
}

LinkedList<Ticket> getAllTicket()
{
    LinkedList<Ticket> tickets;

    std::ifstream inFile("./Database/TicketDB/ticket_ID.txt");
    if (!inFile.is_open())
    {
        printError("Error open file ticket_ID.txt");
    }
    std::string x;

    // Create a new Ticket object
    // Get each Ticket from database then add it to the list of Tickets
    while (getline(inFile, x))
    {
        Ticket ticket = getTicketFromDatabase(x);
        tickets.addLast(ticket);
    }

    inFile.close();
    return tickets;
}

void printTicket(Ticket ticket)
{
    TextTable table;

    table.add("   ID vé   ");
    table.add("   ID chuyến bay   ");
    table.add("    Điểm đi    ");
    table.add("    Điểm đến   ");
    table.add("  Loại vé  ");
    table.add("  Ngày khởi hành  ");
    table.add("   Số lượng vé   ");
    table.add("    Giá vé");
    table.endOfRow();

    // table.add(std::to_string(ticket.getID_ve()));
    table.add(ticket.getID_chuyenBay());
    table.add(ticket.getdiemDi());
    table.add(ticket.getdiemDen());
    table.add(ticket.getloaiVe());
    table.add(ticket.getngayKhoiHanh());
    table.add(std::to_string(ticket.getsoLuongVe()));
    table.add(formatCurrency(ticket.getgiaVe()));
    table.endOfRow();

    std::cout << table << std::endl;
}

void printAllTickets(LinkedList<Ticket> tickets)
{
    if (tickets.length() == 0)
    {
        printError("No ticket found!");
        system("pause");
        return;
    }
    TextTable table;

    table.add("Số thứ tự");
    table.add("ID chuyến bay");
    table.add("Điểm đi");
    table.add("Điểm đến");
    table.add("Loại vé");
    table.add("Ngày khởi hành");
    table.add("Số lượng vé");
    table.add("Giá vé");
    table.endOfRow();

    for (int i = 0; i < tickets.length(); i++)
    {
        Ticket ticket = tickets.get(i);
        table.add(std::to_string(i+1));
        table.add(ticket.getID_chuyenBay());
        table.add(ticket.getdiemDi());
        table.add(ticket.getdiemDen());
        table.add(ticket.getloaiVe());
        table.add(ticket.getngayKhoiHanh());
        table.add(std::to_string(ticket.getsoLuongVe()));
        table.add(formatCurrency(ticket.getgiaVe()));
        table.endOfRow();
    }

    std::cout << table << std::endl;
}



void searchByTicketsID()
{
    std::string id = getStringInput("Enter ID");
    if (!isValidTicketId(id))
    {
        printError("Invalid ID, please enter again!");
    }
    else
    {
        Ticket ticket = getTicketFromDatabase(id);
        printTicket(ticket);
    }
}

LinkedList<Ticket> searchByTicketCase(std::string StarttoSearch, std::string EndtoSearch)
{
    LinkedList<Ticket> res;
    LinkedList<Ticket> tickets = getAllTicket();

    for (int i = 0; i < tickets.length(); i++)
    {
        if (findCaseInsensitive(tickets.get(i).getdiemDen(), StarttoSearch) != std::string::npos &&
            findCaseInsensitive(tickets.get(i).getdiemDi(), EndtoSearch) != std::string::npos)
        {
            res.addLast(tickets.get(i));
        }
    }
    return res;
}

void searchByTicketsPath()
{
    std::string diemDi = getStringInput("Điểm đi: ");
    std::string diemDen = getStringInput("Điểm đến: ");
    LinkedList<Ticket> tickets = searchByTicketCase(diemDi, diemDen);

    if (tickets.length())
    {
        printSuccess("Tìm thấy vé!");
        printAllTickets(tickets);
    }
    else
    {
        printError("Không có chuyến bay nào!");
    }
}
void updateTicketQuantityInDatabase( int quantity)
{
    if (quantity == 0)
    {
            printSuccess("Ticket SOLD OUT");
    }
}
