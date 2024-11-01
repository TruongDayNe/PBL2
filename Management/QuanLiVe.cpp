#include "QuanLiVe.h"

bool isValidTicketId(int ticketID)
{
    std::ifstream inFile("./Database/TicketDB/ticket_ID.txt");
    std::string x;
    while (getline(inFile, x))
    {
        if (stoi(x) == ticketID)
        {
            return true;
        }
    }
    inFile.close();
    return false;
}

void addTicketToDatabase(Ticket &ticket)
{
    // generate file path
    // start from main.cpp
    std::string fileName = std::to_string(ticket.getID_ve()) + ".txt";
    std::string filePath = "./Database/TicketDB/" + fileName;

    // create file in database
    std::ofstream outFile(filePath);
    // outFile << computer.ID() << endl;
    outFile << ticket.getID_ve() << std::endl;
    outFile << ticket.getID_chuyenBay() << std::endl;
    outFile << ticket.getloaiVe() << std::endl;
    outFile << ticket.getdiemDi() << std::endl;
    outFile << ticket.getdiemDen() << std::endl;
    outFile << ticket.getngayKhoiHanh() << std::endl;
    outFile << ticket.getsoLuongVe() << std::endl;
    outFile << ticket.getgiaVe() << std::endl;

    if (!isValidTicketId(ticket.getID_ve()))
    {
        std::ofstream outFileTicketId("./Database/TicketDB/ticket_ID.txt", std::ios::app);
        outFileTicketId << ticket.getID_ve() << std::endl;
        outFileTicketId.close();
    }

    // close ofstream
    outFile.close();
}

void addNewTicketToDataBase()
{
    std::cout << spaceLineChoice + "New ticket:\n";
    std::string ID_chuyenBay = getStringInput("ID chuyến bay");
    std::string loaiVe = getStringInput("Loại vé");
    std::string diemDi = getStringInput("Điểm đi");
    std::string diemDen = getStringInput("Điểm đến");
    std::string ngayKhoiHanh = getStringInput("Ngày giờ khởi hành (dd-mm-yy hh:mm:ss)");
    unsigned int soLuongVe = getIntInput("Số lượng vé");
    int giaVe = getIntInput("Giá vé");
    // Create new Ticket object
    Ticket ticket = Ticket(updateLastTicketId(), ID_chuyenBay, diemDi, diemDen, loaiVe, ngayKhoiHanh, soLuongVe, giaVe );

    // Save to database
    addTicketToDatabase(ticket);

    // Update new Ticket id range
    updateLine("./Database/lastID.txt", 0, updateLastTicketId());

    // // Generate sale and write to sale file
    // ofstream outFilesale("./Database/saleSummary.txt", ios::app);
    // outFilesale << ticket.getID_ve() << " " << ticket.getsoGhe() << endl;
    // outFilesale.close();
}

Ticket getTicketFromDatabase(int ticketID)
{
    std::string fileName = std::to_string(ticketID) + ".txt";
    std::string filePath = "./Database/TicketDB/" + fileName;

    std::ifstream inFile(filePath);
    std::string line;

    std::string ID_chuyenBay;
    std::string diemDi;
    std::string diemDen;
    std::string loaiVe;
    std::string ngayKhoiHanh;
    int soLuongVe;
    int giaVe;


    getline(inFile, line);
    ticketID = stoi(line);

    getline(inFile, line);
    ID_chuyenBay = line;

    getline(inFile, line);
    diemDi = line;

    getline(inFile, line);
    diemDen = line;

    getline(inFile, line);
    loaiVe = line;

    getline(inFile, line);
    ngayKhoiHanh = line;

    getline(inFile, line);
    soLuongVe = stoi(line);

    getline(inFile, line);
    giaVe = stoi(line);

    return  Ticket(updateLastTicketId(), ID_chuyenBay, diemDi, diemDen, loaiVe, ngayKhoiHanh, soLuongVe, giaVe);
}
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

void updateTicketInDatabase(int ticketID)
{
    Ticket ticket = getTicketFromDatabase(ticketID);
    std::string filePath = "./Database/TicketDB/";
    std::string fileName = std::to_string(ticketID) + ".txt";

    char char_filePath[(filePath + fileName).length() + 1];
    strcpy(char_filePath, (filePath + fileName).c_str());

    int status = remove(char_filePath);

    std::string ID_chuyenBay = updateComponent("ID chuyến bay", ticket.getID_chuyenBay());
    std::string diemDi = updateComponent("Điểm đi", ticket.getdiemDi());
    std::string diemDen = updateComponent("Điểm đến", ticket.getdiemDen());
    std::string loaiVe = updateComponent("Loại vé", ticket.getloaiVe());
    std::string ngayKhoiHanh = updateComponent("Ngày khởi hành (dd-mm-yy hh:mm:ss)", ticket.getngayKhoiHanh());
    int soLuongVe = updateIntComponent("Số lượng vé", ticket.getsoLuongVe());
    int giaVe = updateIntComponent("Giá vé", ticket.getgiaVe());

    ticket.setID_ve(ticketID);
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
        Ticket ticket = getTicketFromDatabase(stoi(x));
        tickets.addLast(ticket);
    }

    inFile.close();
    return tickets;
}

void printTicket(Ticket ticket)
{
    TextTable table;

    table.add("ID vé");
    table.add("ID chuyến bay");
    table.add("Điểm đi");
    table.add("Điểm đến");
    table.add("Loại vé");
    table.add("Ngày khởi hành");
    table.add("Số lượng vé");
    table.add("Giá vé");
    table.endOfRow();

    table.add(std::to_string(ticket.getID_ve()));
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

void printAllTickets(LinkedList<Ticket> tickets = getAllTicket())
{

    TextTable table;

    table.add("ID vé");
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
        table.add(std::to_string(ticket.getID_ve()));
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
    int id = getIntInput("Enter ID");
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
void updateTicketQuantityInDatabase(int id, int quantity)
{
    updateLine("./Database/TicketDB/" + std::to_string(id) + ".txt", 3, quantity);
}
