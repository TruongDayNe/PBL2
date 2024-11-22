#pragma once

#include "../Business/KhachHang.h"
#include "../Menu/KhachHangMenu.h"
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>

class KhachHang;

// Function prototypes
bool isValidKhachHangID(int KhachHangID);
void addKhachHangToDatabase(KhachHang &KhachHang);
KhachHang addNewKhachHang(bool = true);
KhachHang getKhachHangFromDatabase(int KhachHangID);
void deleteKhachHangFromDatabase(int KhachHangID);
void updateKhachHangInDatabase(int KhachHangID);
void printKhachHang(KhachHang &khachHang);