#pragma once

#include "../Business/KhachHang.h"  // Only include the header file, not the implementation file
#include "../LinkedList.h"
#include "../Library/Console.h"
#include "../Library/Table.cpp"
#include "../Menu/KhachHangMenu.cpp"
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>

// Function prototypes
bool isValidKhachHangID(int KhachHangID);
void addKhachHangToDatabase(KhachHang &KhachHang);
KhachHang addNewKhachHang();
KhachHang getKhachHangFromDatabase(int KhachHangID);
void deleteKhachHangFromDatabase(int KhachHangID);
void updateKhachHangInDatabase(int KhachHangID);
