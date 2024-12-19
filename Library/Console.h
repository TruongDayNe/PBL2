// utils.h
#pragma once

#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <set>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <conio.h>
#include "../LinkedList.h"

// Constants
extern std::string spaceLine;
extern std::string spaceLineChoice;

// Function Prototypes
std::string currentDateTime();
time_t convertToTimeT(const std::string& dateTime);
bool isExpired(const std::string& dateTime);
void printLineColor(std::string line, int color_code);
std::string getStringInput(std::string title);
int getIntInput(std::string title);
bool isNumber(std::string s);
void printError(std::string status);
int updateLastTicketId();
std::string getYesNoInput(std::string title);
std::string updateComponent(std::string key, std::string value);
int updateIntComponent(std::string key, int value);
void updateLine(std::string path, int numLine, int replaceValue);
void updateLine(std::string path, std::string inLine, std::string replaceValue);
void printSuccess(std::string status);
void eraseFileLine(std::string path, std::string eraseLine);
void eraseFileLine(std::string path, int eraseLine);
std::string formatInt(int num);
std::string formatCurrency(int price);
size_t findCaseInsensitive(std::string data, std::string toSearch, size_t pos = 0);
bool isEmail(std::string email);
std::string getEmailInput();
std::string getPasswordInput(std::string title);
LinkedList<std::string> getAllEmail();
bool isUniqueEmail(std::string emailToCheck);
int getLastKhachHangId();
int getLastTicketId();
std::string getReceiptDateTime(int patientID, std::string recID);
int getReceiptTotal(int patientID, std::string recID);
int updatePrice(int old_price);
std::string updatePassword(std::string old_pass);
std::string trim(const std::string& str);
int findLine(const std::string& filename, const std::string& targetLine);
std::string getDateFromString(const std::string &dateTime);
std::string getTimeFromString(const std::string &dateTime);
std::string extractFlightID(const std::string& ticketID);
std::string extractNumbers(const std::string& input);
bool taoSoDoGhe(int soGhe, const std::string& ID_chuyenBay);
int getSeatIndex(const std::string& seatCode);
std::string extractSeatFromTicketID(const std::string& ticketID);
std::string getIssueDate(const std::string& recID);

#endif