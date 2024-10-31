#pragma once
#include "../Business/Ticket.h"
#include "../Business/Ticket.cpp"
#include "../LinkedList.h"
#include "../Library/Console.cpp"
#include "../Library/Table.cpp"
#include <fstream>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;

bool isValidTicketId(int ticketID)
{
    ifstream inFile("./Database/TicketDB/ticket_ID.txt");
    string x;
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
    string fileName = to_string(ticket.getID_ve()) + ".txt";
    string filePath = "./Database/TicketDB/" + fileName;

    // create file in database
    ofstream outFile(filePath);
    // outFile << computer.ID() << endl;
    outFile << ticket.getID_ve() << endl;
    outFile << ticket.getID_chuyenBay() << endl;
    outFile << ticket.getloaiVe() << endl;
    outFile << ticket.getdiemDi() << endl;
    outFile << ticket.getdiemDen() << endl;
    outFile << ticket.getngayKhoiHanh() << endl;
    outFile << ticket.getsoLuongVe() << endl;
    outFile << ticket.getgiaVe() << endl;

    if (!isValidTicketId(ticket.getID_ve()))
    {
        ofstream outFileTicketId("./Database/TicketDB/ticket_ID.txt", ios::app);
        outFileTicketId << ticket.getID_ve() << endl;
        outFileTicketId.close();
    }

    // close ofstream
    outFile.close();
}

void addNewTicketToDataBase()
{
    cout << spaceLineChoice + "New ticket:\n";
    string ID_chuyenBay = getStringInput("ID chuyến bay");
    string loaiVe = getStringInput("Loại vé");
    string diemDi = getStringInput("Điểm đi");
    string diemDen = getStringInput("Điểm đến");
    string ngayKhoiHanh = getStringInput("Ngày giờ khởi hành (dd-mm-yy hh:mm:ss)");
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
    string fileName = to_string(ticketID) + ".txt";
    string filePath = "./Database/TicketDB/" + fileName;

    ifstream inFile(filePath);
    string line;

    string ID_chuyenBay;
    string diemDi;
    string diemDen;
    string loaiVe;
    string ngayKhoiHanh;
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
    string filePath = "./Database/TicketDB/";
    string fileName = to_string(ticketID) + ".txt";

    // char char_filePath[(filePath + fileName).length() + 1];
    // strcpy(char_filePath, (filePath + fileName).c_str());

    int status = remove((filePath + fileName).c_str());

    if (status == 0)
    {
        printSuccess("Succesfully delete this Ticket!");
        eraseFileLine(filePath + "ticket_ID.txt", to_string(ticketID));
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
    string filePath = "./Database/TicketDB/";
    string fileName = to_string(ticketID) + ".txt";

    char char_filePath[(filePath + fileName).length() + 1];
    strcpy(char_filePath, (filePath + fileName).c_str());

    int status = remove(char_filePath);

    string ID_chuyenBay = updateComponent("ID chuyến bay", ticket.getID_chuyenBay());
    string diemDi = updateComponent("Điểm đi", ticket.getdiemDi());
    string diemDen = updateComponent("Điểm đến", ticket.getdiemDen());
    string loaiVe = updateComponent("Loại vé", ticket.getloaiVe());
    string ngayKhoiHanh = updateComponent("Ngày khởi hành (dd-mm-yy hh:mm:ss)", ticket.getngayKhoiHanh());
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

    ifstream inFile("./Database/TicketDB/ticket_ID.txt");
    if (!inFile.is_open())
    {
        printError("Error open file ticket_ID.txt");
    }
    string x;

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
    table.add("Số lượng vé");
    table.add("Giá vé");
    table.endOfRow();

    table.add(to_string(ticket.getID_ve()));
    table.add(ticket.getID_chuyenBay());
    table.add(ticket.getdiemDi());
    table.add(ticket.getdiemDen());
    table.add(ticket.getloaiVe());
    table.add(to_string(ticket.getsoLuongVe()));
    table.add(formatCurrency(ticket.getgiaVe()));
    table.endOfRow();

    cout << table << endl;
}

void printAllTickets(LinkedList<Ticket> tickets = getAllTicket())
{

    TextTable table;

    table.add("ID vé");
    table.add("ID chuyến bay");
    table.add("Điểm đi");
    table.add("Điểm đến");
    table.add("Loại vé");
    table.add("Số lượng vé");
    table.add("Giá vé");
    table.endOfRow();

    for (int i = 0; i < tickets.length(); i++)
    {
        Ticket ticket = tickets.get(i);
        table.add(to_string(ticket.getID_ve()));
        table.add(ticket.getID_chuyenBay());
        table.add(ticket.getdiemDi());
        table.add(ticket.getdiemDen());
        table.add(ticket.getloaiVe());
        table.add(to_string(ticket.getsoLuongVe()));
        table.add(formatCurrency(ticket.getgiaVe()));
        table.endOfRow();
    }

    cout << table << endl;
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

LinkedList<Ticket> searchByTicketCase(string StarttoSearch, string EndtoSearch)
{
    LinkedList<Ticket> res;
    LinkedList<Ticket> tickets = getAllTicket();

    for (int i = 0; i < tickets.length(); i++)
    {
        if (findCaseInsensitive(tickets.get(i).getdiemDen(), StarttoSearch) != string::npos &&
            findCaseInsensitive(tickets.get(i).getdiemDi(), EndtoSearch) != string::npos)
        {
            res.addLast(tickets.get(i));
        }
    }
    return res;
}

void searchByTicketsPath()
{
    string diemDi = getStringInput("Điểm đi: ");
    string diemDen = getStringInput("Điểm đến: ");
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
    updateLine("./Database/TicketDB/" + to_string(id) + ".txt", 3, quantity);
}
