#pragma once
#include "../Business/Ticket.h"
#include "../LinkedList.h"
#include "../Library/Console.h"
#include "../Library/Table.cpp"
#include <fstream>
#include <string>
#include <iostream>
#include <string>

bool isValidTicketId(std::string ticketID);
void addTicketToDatabase(Ticket &ticket);
void addNewTicketToDataBase();
Ticket getTicketFromDatabase(std::string ticketID);
void deleteTicketFromDatabase(std::string ticketID);
void updateTicketInDatabase(std::string ticketID);
LinkedList<Ticket> getAllTicket();
void printTicket(Ticket ticket);
void printAllTickets(LinkedList<Ticket> tickets = getAllTicket());
void searchByTicketsID();
LinkedList<Ticket> searchByTicketCase(std::string StarttoSearch, std::string EndtoSearch);
LinkedList<Ticket> searchByTicketsPath();
void updateTicketQuantityInDatabase(std::string id, int quantity); 