#pragma once
#include "../Business/Flight.h"
#include "../Business/Ticket.h"
#include "../LinkedList.h"
#include "../Library/Console.h"
#include "../Library/Table.cpp"
#include <fstream>
#include <string>
#include <iostream>
#include <string>

bool isValidFlightID(const std::string& flightID);
void addFlightToDatabase(Flight &Flight);
void addNewFlightToDataBase();
Flight getFlightFromDatabase(std::string flightID);
void deleteFlightFromDatabase(std::string flightID);
void updateFlightInDatabase(std::string flightID);
LinkedList<Flight> getAllFlight();
void printFlight(Flight Flight);
void printAllFlights(LinkedList<Flight> flights = getAllFlight());
void searchByFlightsID();
LinkedList<Flight> searchByFlightCase(std::string StarttoSearch, std::string EndtoSearch);
LinkedList<Flight> searchByFlightsPath();
void updateTicketQuantityInDatabase(const std::string& flightID, int quantity);