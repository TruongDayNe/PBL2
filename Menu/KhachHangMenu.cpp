#pragma once
#include "Menu.h"
#include "../Management/QuanLiKhachHang.cpp"
#include "../Management/QuanLiVe.cpp"
#include "../Management/QuanLiNguoiDung.cpp"
#include "../Library/Console.cpp"
#include <iostream>
using namespace std;

void KhachHangMenu::main()
{
    system("cls");
    ifstream inFile("./Page/KhachHang.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    char data[200][200] =
        {
            "\t   Login",
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
void KhachHangMenu::login()
{
    system("cls");

    int time = 3;
    int id = -1;
    do
    {
        ifstream inFile("./Page/KhachHangLogin.txt");
        string line;
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
        inFile.close();
        string email = getEmailInput();
        string password = getPasswordInput("Password");

        id = findUser(email, password);
        if (id == -1)
        {
            time--;
            if (time != 0)
            {
                printError("Invalid email/password, please enter again!");
                system("pause");
                system("cls");
            }
            else
            {
                printError("You have reached maximum login attempts, please try again later!");
                system("pause");
                KhachHangMenu::main();
            }
        }
        else
        {
            KhachHang KhachHang = getKhachHangFromDatabase(id);
            KhachHangMenu::menu(KhachHang);
        }
    } while (id = -1);
}
void KhachHangMenu::signUp()
{
    system("cls");
    ifstream inFile("./Page/KhachHangSignUp.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    KhachHang KhachHang = addNewKhachHang();
    KhachHangMenu::menu(KhachHang);
}

void KhachHangMenu::menu(KhachHang &KhachHang)
{
    system("cls");

    while (true)
    {
        int key = KhachHangMenu::printTask();
        switch (key)
        {
        case 1:
        {
            // KhachHang = getKhachHangFromDatabase(KhachHang.getID()); // KhachHangManagement,user
            // printKhachHang(KhachHang);                             // KhachHangManagement
            system("pause");
            KhachHangMenu::menu(KhachHang);
        }
        break;

        case 2:
        {
            // updateKhachHangInDatabase(KhachHang.getID()); // KhachHangManagement
            system("pause");
            KhachHangMenu::menu(KhachHang);
        }
        break;

        case 3:
        {
            // orderDrugHistory(KhachHang);
            system("pause");
            KhachHangMenu::menu(KhachHang);
        }
        break;

        case 4:
        {
            // KhachHang.printAllDrug(); // Business/User
            system("pause");
            KhachHangMenu::menu(KhachHang);
        }
        break;

        case 5:
        {
            // searchDrug(KhachHang);
            system("pause");
            KhachHangMenu::menu(KhachHang);
        }
        break;

        case 6:
        {
            // purchaseDrug(KhachHang);
            system("pause");
            KhachHangMenu::menu(KhachHang);
        }
        break;

        case 7:
        {
            // bookAppointment(KhachHang);
            system("pause");
            KhachHangMenu::menu(KhachHang);
        }
        break;

        case 8:
        {
            // viewMedicalHistory(KhachHang);
            system("pause");
            KhachHangMenu::menu(KhachHang);
        }
        break;

        case 9:
            Home::menu();
            break;
        }
    }
}

int KhachHangMenu::printTask()
{
    system("cls");
    ifstream inFile("./Page/KhachHangMenu.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();

    char data[200][200] =
        {
            "\t  Account information",
            "\t  Update account information",
            "\t  View your drug order history",
            "\t  View all drugs",
            "\t  Search drug information",
            "\t  Purchase drug",
            "\t  Book an appointment",
            "\t  View medical history",
            "\t  Log out",
        };

    MenuBox MENU(9, data);
    int key = MENU.menu();
    return key;
}