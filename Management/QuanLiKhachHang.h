#pragma once

#include "D:/Code/PBL2/Business/KhachHang.h"  // Only include the header file, not the implementation file
#include "D:/Code/PBL2/Menu/KhachHangMenu.h"
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>

class KhachHang;

// Function prototypes
bool isValidKhachHangID(int KhachHangID);
void addKhachHangToDatabase(KhachHang &KhachHang);
KhachHang addNewKhachHang();
KhachHang getKhachHangFromDatabase(int KhachHangID);
void deleteKhachHangFromDatabase(int KhachHangID);
void updateKhachHangInDatabase(int KhachHangID);
void printKhachHang(KhachHang &khachHang);