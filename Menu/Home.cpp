#pragma once
#include <fstream>
#include "Menu.h"


void Home::welcome()
{

    ifstream inFile("./Page/Intro.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    system("pause");
    system("cls");
}
int Home::printTask()
{
    ifstream inFile("./Page/MainPage.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();

    char data[200][200] =
        {
            "\t   Customer",
            "\t   Admin",
            "\t   Exit",
        };

    MenuBox MENU(3, data);
    int key = MENU.menu();
    return key;
}

void Home::menu()
{
    int key = Home::printTask();
    switch (key)
    {
    case 1:
        KhachHangMenu::main();
        system("pause");
        break;

    case 2:
        AdminMenu::main();
        system("pause");
        break;

    case 3:
        exit(0);
        break;
    }
}