#include "KhachHangMenu.h"

void KhachHangMenu::KH_main()
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
                KhachHangMenu::KH_main();
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
            LinkedList<Flight> flights_foundByPath  = searchByFlightsPath();
            purchaseTicket(khachHang, flights_foundByPath);
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
        {
            cancelTicket(khachHang);
            system("pause");
            KhachHangMenu::menu(khachHang);
        }
        break;

        case 7:
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
            "\t  Search tickets",
            "\t  Purchase ticket",
            "\t  Cancel ticket",
            "\t  Log out",
        };

    MenuBox MENU(7, data);
    int key = MENU.menu();
    return key;
}

//Thêm ticket vào cart để mua
void KhachHangMenu::purchaseTicket(KhachHang &khachHang, LinkedList<Flight> flights)
{
    int soLuongMua, new_soLuongVe;
    std::string ID_chuyenBay;
    std::string request;

    do
    {
        system("cls");
        printAllFlights(flights);

        if (flights.length() == 0)
        {
            printError("No Tickets found!");
            system("pause");
            menu(khachHang);
            return;
        }
    
        ID_chuyenBay = getStringInput("Please enter the Flight ID that you want to purchase");
        while (!isValidFlightID(ID_chuyenBay))
        {
            printError("Invalid Ticket ID, please enter again!");
            ID_chuyenBay = getStringInput("Please enter the Ticket ID that you want to purchase");
        }
        Flight flight = getFlightFromDatabase(ID_chuyenBay);

        soLuongMua = getIntInput("Please enter the quantity you want to purchase");
        while (soLuongMua > flight.getsoLuongVe() || soLuongMua < 1)
        {
            printError("Invalid Ticket quantity, please enter again!");
            soLuongMua = getIntInput("Please enter the quantity you want to purchase");
        }
        // Get flight once before loop to avoid multiple database calls
        Flight currentFlight = getFlightFromDatabase(ID_chuyenBay);
        
        // Store tickets to add before updating quantity
        LinkedList<Ticket> ticketsToAdd;
        for (int i = 0; i < soLuongMua; ++i)
        {
            KhachHang ticket_owner = addNewKhachHang(false);
            
            // Get ticket from flight's ticket list
            if (currentFlight.tickets.length() > 0) {
                Ticket ticket = currentFlight.tickets.get(i);
                
                // Create new ticket with unique ID and owner
                Ticket newTicket(ticket.getID_ve(), currentFlight, ticket_owner, ticket.getGhe(), ticket.getgiaVe());
                
                ticketsToAdd.addLast(newTicket);
            }
        }

        // Update available tickets
        new_soLuongVe = flight.getsoLuongVe() - soLuongMua;
        updateTicketQuantityInDatabase(ID_chuyenBay, new_soLuongVe);
        
        // Remove used tickets from flight
        for (int i = 0; i < soLuongMua; i++) {
            currentFlight.tickets.removeAtIndex(0);
        }
        
        // Add all tickets to cart
        for (int i = 0; i < ticketsToAdd.length(); i++) {
            khachHang.getCart().addTickettoCart(ticketsToAdd.get(i));
        } 
        request = getYesNoInput(spaceLineChoice + "Do you want to purchase more tickets? (y/n)");
    } while (request == "y" || request == "Y");
    
    khachHang.purchase();
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
        khachHang.printAllKhachHangPurchases();
        // cout << spaceLine << "1. View receipt details by ID\n";
        // cout << spaceLine << "2. Back\n";
        char data[200][200] =
            {
                "\t   View ticket details by ID",
                "\t   Back",
            };

        MenuBox MENU(2, data);
        int key = MENU.menu();
        switch (key)
        {
        case 1:
        {
            std::string ticketID = getStringInput("Enter the ticket ID you want to view details");
            while (!isValidTicketID(ticketID))
            {
                printError("Invalid ticket ID, please enter again!");
                ticketID = getStringInput("Enter the ticket ID you want to view details");
            }
            std::cout << std::endl;
            // Handle Exception
            printTicket(khachHang.getID(), findTicketById(ticketID));
            system("pause");
            orderTicketHistory(khachHang);
        }
        break;

        case 2:
            // KhachHangMenu::menu(khachHang);
            break;
        }
    }
}

void cancelTicket(KhachHang &khachHang)
{
    if (khachHang.Rec().length() == 0)
    {
        printError("You haven't purchased any tickets to cancel!");
        system("pause");
        KhachHangMenu::menu(khachHang);
        return;
    }

    system("cls");
    khachHang.printAllKhachHangPurchases();

    std::string ticketID = getStringInput("Enter the Ticket ID you want to cancel");
    while (!isValidTicketID(ticketID))
    {
        printError("Invalid Ticket ID, please enter again!");
        ticketID = getStringInput("Enter the Ticket ID you want to cancel");
    }

    // Find the ticket in the customer's records
    Ticket ticketToCancel;
    bool found = false;
    for (int i = 0; i < khachHang.Rec().length(); ++i)
    {
        LinkedList<Ticket> tickets = getTicketFromReceipt(khachHang.Rec().get(i));
        for (int j = 0; j < tickets.length(); ++j)
        {
            if (tickets.get(j).getID_ve() == ticketID)
            {
                ticketToCancel = tickets.get(j);
                found = true;
                break;
            }
        }
        if (found)
            break;
    }

    if (!found)
    {
        printError("Ticket not found in your purchases!");
        system("pause");
        cancelTicket(khachHang);
        return;
    }

    // Confirm cancellation
    std::string confirm = getYesNoInput("Are you sure you want to cancel this ticket? (y/n)");
    if (confirm != "y" && confirm != "Y")
    {
        printSuccess("Ticket canceled.");
        system("pause");
        return;
    }

    // Remove the ticket from the customer's cart
    // khachHang.getCart().removeTicketFromCart(ticketID);

    // Update ticket availability in the flight's record
    Flight flight = ticketToCancel.getChuyenBay();
    int updatedQuantity = flight.getsoLuongVe() + 1;
    updateTicketQuantityInDatabase(flight.getID_chuyenBay(), updatedQuantity);

    // Remove ticket from the customer's receipts
    for (int i = 0; i < khachHang.Rec().length(); ++i)
    {
        LinkedList<Ticket> tickets = getTicketFromReceipt(khachHang.Rec().get(i));
        for (int j = 0; j < tickets.length(); ++j)
        {
            if (tickets.get(j).getID_ve() == ticketID)
            {
                tickets.removeAtIndex(j);
                break;
            }
        }
    }

    printSuccess("Ticket canceled successfully!");
    system("pause");
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