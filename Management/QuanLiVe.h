#pragma once

#include "../Business/Ticket.h"
#include "../LinkedList.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstring>

using namespace std;

// Kiểm tra xem ID vé có hợp lệ hay không
bool isValidTicketId(int ticketID);

// Thêm vé vào cơ sở dữ liệu
void addTicketToDatabase(Ticket &ticket);

// Thêm vé mới vào cơ sở dữ liệu
void addNewTicketToDataBase();

// Lấy vé từ cơ sở dữ liệu dựa trên ID
Ticket getTicketFromDatabase(int ticketID);

// Xóa vé khỏi cơ sở dữ liệu
void deleteTicketFromDatabase(int ticketID);

// Cập nhật vé trong cơ sở dữ liệu
void updateTicketInDatabase(int ticketID);

// Lấy tất cả vé từ cơ sở dữ liệu
LinkedList<Ticket> getAllTicket();

// In thông tin vé
void printTicket(Ticket ticket);

// In tất cả vé
void printAllTickets(LinkedList<Ticket> tickets);

// Tìm kiếm vé theo ID
void searchByTicketsID();

// Tìm kiếm vé theo tên chuyến bay
LinkedList<Ticket> searchByTicketCase(string toSearch);

// Tìm kiếm vé theo tên
void searchByTicketsName();

// Cập nhật số lượng vé trong cơ sở dữ liệu
void updateTicketQuantityInDatabase(int id, int quantity);
