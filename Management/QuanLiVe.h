#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>

#include "../Library/Console.h"
#include "../Business/Ticket.h"
#include "QuanLiChuyenBay.h"

class KhachHang;

// Function prototypes
std::string lineTicketFormat(std::string key, std::string info);
std::string lineTicketFormat(std::string qty, std::string item, std::string amount);

void printTicket(int KhachHangID, Ticket ticket);

bool isValidTicketID(std::string ticketID, KhachHang &KhachHang);

bool isValidTicketID(std::string ticketID) ;

void getTicketFromDatabase(int KhachHangID, Ticket ticket);

// void getAllKhachHangTickets(KhachHang &KhachHang); 

void addTicketToDatabase(int KhachHangID, Cart _Cart, LinkedList<std::string> ticketID);

void deleteTicketFromDatabase(int KhachHangID, std::string ticketID);

Ticket findTicketById(const std::string& ticketID);

// LinkedList<Ticket> getTicketFromReceipt(std::string recID);

// LinkedList<std::string> getKhachHangIDFromReceipt(std::string recID);

void removeTicketFromReceipt(std::string recID, std::string ticketID);

//needed
std::string getKhachHangNameFromDatabase(int KhachHangID);
