#pragma once
#include "../Business/Ticket.h"
#include "../LinkedList.h"
#include "../Library/Console.h"
#include "../Library/Table.cpp"
#include <fstream>
#include <string>
#include <iostream>
#include <string>

bool isValidTicketId(const std::string& filghtID);
void addTicketToDatabase(Ticket &ticket);
void addNewTicketToDataBase();
Ticket getTicketFromDatabase(std::string ticketID);
// Ticket getTicketFromDatabase(int ticketID);
void deleteTicketFromDatabase(int ticketID);
void updateTicketInDatabase(int ticketID);
LinkedList<Ticket> getAllTicket();
void printTicket(Ticket ticket);
void printAllTickets(LinkedList<Ticket> tickets = getAllTicket());
void searchByTicketsID();
LinkedList<Ticket> searchByTicketCase(std::string StarttoSearch, std::string EndtoSearch);
void searchByTicketsPath();
void updateTicketQuantityInDatabase( int quantity); 