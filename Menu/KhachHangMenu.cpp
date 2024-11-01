#include "KhachHangMenu.h"

void KhachHangMenu::main()
{
    system("cls");
    // ifstream inFile("./Page/KhachHang.txt");
    // string line;
    // while (getline(inFile, line))
    // {
    //     cout << line << endl;
    // }
    // inFile.close();
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
        // ifstream inFile("./Page/KhachHangLogin.txt");
        // string line;
        // while (getline(inFile, line))
        // {
        //     cout << line << endl;
        // }
        // inFile.close();
        std::string email = getEmailInput();
        std::string password = getPasswordInput("Password");

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
    } while (id == -1);
}
void KhachHangMenu::signUp()
{
    system("cls");
    // ifstream inFile("./Page/KhachHangSignUp.txt");
    // string line;
    // while (getline(inFile, line))
    // {
    //     cout << line << endl;
    // }
    // inFile.close();
    KhachHang KhachHang = addNewKhachHang();
    KhachHangMenu::menu(KhachHang);
}

void KhachHangMenu::menu(KhachHang &khachHang)
{
    system("cls");

    while (true)
    {
        int key = KhachHangMenu::printTask();
        switch (key)
        {
        case 1:
        {
            khachHang = getKhachHangFromDatabase(khachHang.getID()); // KhachHangManagement,user
            printKhachHang(khachHang);                             // KhachHangManagement
            system("pause");
            KhachHangMenu::menu(khachHang);
        }
        break;

        case 2:
        {
            updateKhachHangInDatabase(khachHang.getID()); // KhachHangManagement
            system("pause");
            KhachHangMenu::menu(khachHang);
        }
        break;

        case 3:
        {
            orderTicketHistory(khachHang);
            system("pause");
            KhachHangMenu::menu(khachHang);
        }
        break;

        case 4:
        {
            khachHang.printAllTicket(); // Business/User
            system("pause");
            KhachHangMenu::menu(khachHang);
        }
        break;

        case 5:
        {
            purchaseTicket(khachHang);
            system("pause");
            KhachHangMenu::menu(khachHang);
        }
        break;

        case 6:
            Home::menu();
            break;
        }
    }
}

int KhachHangMenu::printTask()
{
    system("cls");
    // ifstream inFile("./Page/KhachHangMenu.txt");
    // string line;
    // while (getline(inFile, line))
    // {
    //     cout << line << endl;
    // }
    // inFile.close();

    char data[200][200] =
        {
            "\t  Account information",
            "\t  Update account information",
            "\t  View your ticket order history",
            "\t  View all tickets",
            "\t  Purchase drug",
            "\t  Log out",
        };

    MenuBox MENU(6, data);
    int key = MENU.menu();
    return key;
}

void KhachHangMenu::purchaseTicket(KhachHang &khachHang)
{
    system("cls");

    khachHang.printAllTicket();

    int ID_ve, soLuongMua, new_soLuongVe;
    std::string request;

    do
    {
        ID_ve = getIntInput("Please enter the Ticket ID that you want to purchase");
        while (!isValidTicketId(ID_ve))
        {
            printError("Invalid Ticket ID, please enter again!");
            ID_ve = getIntInput("Please enter the Ticket ID that you want to purchase");
        }
        Ticket Ticket = getTicketFromDatabase(ID_ve);
        soLuongMua = getIntInput("Please enter the quantity you want to purchase");
        while (soLuongMua > Ticket.getsoLuongVe() || soLuongMua < 1)
        {
            printError("Invalid Ticket quantity, please enter again!");
            soLuongMua = getIntInput("Please enter the quantity you want to purchase");
        }
        new_soLuongVe = Ticket.getsoLuongVe() - soLuongMua;
        updateTicketQuantityInDatabase(ID_ve, new_soLuongVe);
        khachHang.getCart().addTickettoCart(ID_ve, soLuongMua);
        request = getYesNoInput(spaceLineChoice + "Do you want to purchase another Ticket (y/n)");
    } while (request == "y" || request == "Y");

    khachHang.purchase();
}

void printKhachHang(KhachHang &khachHang)
{
    TextTable table;

    table.add("ID");
    table.add("Name");
    table.add("Email");
    table.endOfRow();

    table.add(std::to_string(khachHang.getID()));
    table.add(khachHang.getName());
    table.add(khachHang.getEmail());
    table.endOfRow();

    std::cout << table << std::endl;
}

void KhachHangMenu::orderTicketHistory(KhachHang &khachHang)
{
    if (khachHang.Rec().length() == 0)
    {
        printError("You haven't purchased anything!");
        system("pause");
        KhachHangMenu::menu(khachHang);
    }
    else
    {
        system("cls");
        khachHang.printAllKhachHangReceipts();
        // cout << spaceLine << "1. View receipt details by ID\n";
        // cout << spaceLine << "2. Back\n";
        char data[200][200] =
            {
                "\t   View receipt details by ID",
                "\t   Back",
            };

        MenuBox MENU(2, data);
        int key = MENU.menu();
        switch (key)
        {
        case 1:
        {
            std::string recID = getStringInput("Enter the receipt ID you want to view details");
            while (!isValidReceiptID(recID, khachHang))
            {
                printError("Invalid receipt ID, please enter again!");
                recID = getStringInput("Enter the receipt ID you want to view details");
            }
            std::cout << std::endl;
            // Handle Exception
            printReceipt(khachHang.getID(), recID);
            system("pause");
            orderTicketHistory(khachHang);
        }
        break;

        case 2:
            KhachHangMenu::menu(khachHang);
            break;
        }
    }
}

// static void KhachHangMenu::searchTicket(KhachHang &khachHang)
// {
//     system("cls");
//     ifstream inFile("./Page/DoctorSearchDrug.txt");
//     string line;
//     while (getline(inFile, line))
//     {
//         cout << line << endl;
//     }
//     inFile.close();

//     char data[200][200] =
//         {
//             "\t   Search by Ticket ID",
//             "\t   Search by Name",
//             "\t   Back",
//         };

//     MenuBox MENU(3, data);
//     int key = MENU.menu();
//     switch (key)
//     {
//     case 1:
//     {
//         khachHang.searchByTicketID();
//         system("pause");
//         KhachHangMenu::searchTicket(khachHang);
//     }
//     break;
//     case 2:
//     {
//         khachHang.searchByReceiptID();
//         system("pause");
//         KhachHangMenu::searchTicket(khachHang);
//     }
//     break;

//     case 3:
//         KhachHangMenu::menu(khachHang);
//         break;
//     }
// }