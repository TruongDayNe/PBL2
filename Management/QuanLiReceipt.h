#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>

#include "../Library/Console.h"
#include "../Business/Ticket.h"
#include "../Management/QuanLiKhachHang.h"
class KhachHang;

// Function prototypes
std::string lineReceiptFormat(std::string key, std::string info);
std::string lineReceiptFormat(std::string qty, std::string item, std::string amount);

void printReceipt(int KhachHangID, std::string recID);

bool isValidReceiptID(std::string recID, KhachHang &KhachHang);

void getReceiptFromDatabase(int KhachHangID, int recID);

void getAllKhachHangReceipts(KhachHang &KhachHang); 

void addReceiptToDatabase(int KhachHangID, Cart _Cart, LinkedList<std::string> Rec);

void deleteReceiptFromDatabase(int KhachHangID, std::string recID);

// Add any additional utility function prototypes here if needed
