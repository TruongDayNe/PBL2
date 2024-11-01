#pragma once // Tránh đụng độ thư viện khi gọi chồng file
#include <iostream>
#include <conio.h>     // Thư viện hỗ trợ nhập xuất ký tự từ bàn phím
#include <cstddef>
#include <windows.h>   // Thư viện chứa các hàm liên quan đến Windows như SetConsoleTextAttribute, SetConsoleCursorPosition
#include <ctime>       // Thư viện hỗ trợ về thời gian thực
//======= lấy tọa độ x của con trỏ hiện tại =============
#define KEY_NONE -1

inline int whereX()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.dwCursorPosition.X;
    return -1;
}
//========= lấy tọa độ y của con trỏ hiện tại =======
inline int whereY()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.dwCursorPosition.Y;
    return -1;
}
//============== dịch con trỏ hiện tại đến điểm có tọa độ (x,y) ==========
inline void gotoXY(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = {(short)x, (short)y}; // Lỗi
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
//============= đặt màu cho chữ =========
inline void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
//============== làm ẩn trỏ chuột ===========
inline void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = {1, CursorVisibility};
    SetConsoleCursorInfo(handle, &cursor);
}
//======= trả về mã phím người dùng bấm =========
inline int inputKey()
{
    if (_kbhit()) // true
    {
        int key = _getch();

        if (key == 224)
        {
            key = _getch();
            return key + 1000;
        }

        return key;
    }
    else
    {
        return KEY_NONE;
    }
    return KEY_NONE;
}
inline void textcolor(int x)
{
    HANDLE mau;
    mau = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(mau, x);
}

inline void ToMau(int x, int y, char *a, int color)
{
    gotoXY(x, y);
    textcolor(color);
    std::cout << a;
    textcolor(7);
}
inline void resizeConsole(int width, int heigth)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, heigth, TRUE);
}

#ifndef MENUBOX_H
#define MENUBOX_H
class MenuBox
{
private:
    int xx = 60, yy = 10, choose = 0;
    int idx = 1;
    int id = 0;
    char **Option;
    int num;

public:
    MenuBox(int, char[200][200]);
    inline void box(int xx, int yy, int w, int h, int t_color, int b_color, char **content, int idx);
    inline void boxes(int xx, int yy, int w, int h, int t_color, int b_color, char **content, int count);
    inline void lightBox(int xx, int yy, int w, int h, int b_color, char **content, int idx);
    void print(int idx, char **content);
    int getChoose(int choose);
    int menu();
};
#endif