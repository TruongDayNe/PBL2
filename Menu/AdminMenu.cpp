#pragma once
#include "Menu.h"
#include "QuanLiVe.h"
#include "Amin"
#include "QuanLiChuyenBay.h"
#include "Console.cpp"
#include <iostream>
using namespace std;

void AdminMenu::main()
{
    system("cls");
    ifstream inFile("PBL2\Menu\AdminMenu.cpp")
        string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    char data[200][200] = {
        "\t Login",
        "\t   Sign Up",
        "\t   Back",
    };
    MenuBox MENU(3, data);
    int key = MENU.menu();
    switch (key)
    {
    case 1:
    {
        KhachHangMenu::login();
        system("pause");
        break;
    }

    case 2:
    {
        KhachHangMenu::signUp();
        system("pause");
        break;
    }

    case 3:
        Home::menu();
        break;
    }
}
void Admin::login()
{
    system("cls");

    const string ADMIN_USERNAME = "admin";
    const string ADMIN_PASSWORD = "admin123";
    int attempts = 3;

    do
    {
        cout << "\n\t\t=== ADMIN LOGIN ===" << endl;
        cout << "\t\t-------------------" << endl;

        string username;
        cout << "\t\tUsername: ";
        cin >> username;

        string password = getPasswordInput("Password");

        if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD)
        {
            cout << "\n\t\tLogin successful!" << endl;
            system("pause");
            AdminMenu::main(); // Chuyển đến menu admin
            return;
        }
        else
        {
            attempts--;
            if (attempts > 0)
            {
                printError("Invalid username/password. " + to_string(attempts) + " attempts remaining.");
                system("pause");
                system("cls");
            }
            else
            {
                printError("You have reached maximum login attempts. Returning to main menu.");
                system("pause");
                return;
            }
        }
    } while (attempts > 0);
}
void Admin::signUp()
{
    system("cls");
    ifstream inFile("./Page/AdminSignUp.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
     KhachHang = addNewKhachHang();
    KhachHangMenu::menu(KhachHang);
}

void AdminMenu::menu(Admin &Admin)
{
    system("cls");

    while (true)
    {
        int key = AdminMenu::printTask();
        switch (key)
        {
        case 1:
            cout << "Nhập ID vé cần tra cứu";
            int ticketID;
            cin >> ticketID;
            searchByTicketsID(ticketID);
            break;
        case 2:
            cout << "Nhập ID vé cần chỉnh sửa";
            int ticketID;
            cin >> ticketID;
            updateTicketInDatabase(ticketID);
            break;
        case 3:
            addNewTicketToDataBase();
            cout<< "Thêm vé thành công";
            printReceipt();

            break;
        case 4: 
            cout << "Nhập ID vé cần hủy";
            int ticketID;
            cin >> ticketID;
            deleteTicketFromDatabase(ticketID);
            cout<<"Hủy vé thành công";
        case 5:

        default:
            break;
        }
    }
}

int AdminMenu::printTask()
{
    system("cls");
    ifstream inFile("./Page/AdminMenu.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();

    char data[200][200] =
        {
            "\t  Tra cứu vé theo ID",
            "\t  Chỉnh sửa thông tin vé",
            "\t  Thêm vé",
            "\t  Hủy vé",
            "\t  Tra cứu thông tin chuyến bay",
        };

    MenuBox MENU(5, data);
    int key = MENU.menu();
    return key;
}
