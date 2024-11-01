#pragma once

#include <string>
#include <ctime>

using namespace std;

// Các hàm xử lý thời gian
string currentDateTime();
time_t convertToTimeT(const string& dateTime);
bool isExpired(const string& dateTime);

// Các hàm xử lý đầu vào/đầu ra
void printLineColor(string line, int color_code);
string getStringInput(string title);
int getIntInput(string title);
bool isNumber(string s);
void printError(string status);
void printSuccess(string status);
string getYesNoInput(string title);

// Các hàm xử lý file
void updateLine(string path, int numLine, int replaceValue);
void updateLine(string path, string inLine, string replaceValue);
void eraseFileLine(string path, string eraseLine);
void eraseFileLine(string path, int eraseLine);

// Các hàm xử lý dữ liệu
string formatInt(int num);
string formatCurrency(int price);
size_t findCaseInsensitive(string data, string toSearch, size_t pos = 0);

// Các hàm xử lý email và mật khẩu
bool isEmail(string email);
string getEmailInput();
string getPasswordInput(string title);
LinkedList<string> getAllEmail();
bool isUniqueEmail(string emailToCheck);

// Các hàm lấy ID và thông tin
int getLastKhachHangId();
int getLastTicketId();
string getReceiptDateTime(int patientID, string recID);
int getReceiptTotal(int patientID, string recID);

// Các hàm cập nhật
int updatePrice(int old_price);
string updatePassword(string old_pass);
string updateComponent(string key, string value);
int updateIntComponent(string key, int value);