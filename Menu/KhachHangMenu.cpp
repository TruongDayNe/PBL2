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
                system("cls");
                printError("Invalid email/password, please enter again!");
                std::cout << "\nAttempts remaining: " << time << "\n";
                system("cls");
            }
            else
            {
                system("cls");
                printError("You have reached maximum login attempts, please try again later!");
                system("pause");
                system("cls");
                KhachHangMenu::KH_main();
            }
        }
        else
        {
            KhachHang KhachHang = getKhachHangFromDatabase(id);
            system("cls");
            printSuccess("Login successful!");
            std::cout << "\nWelcome back, " << KhachHang.getName() << "!" << "\n";
            system("pause");
            system("cls");
            KhachHangMenu::menu(KhachHang);
        }
    } while (id == -1);
}
void KhachHangMenu::signUp()
{
    system("cls");
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
            "\t  Log out",
        };

    MenuBox MENU(5, data);
    int key = MENU.menu();
    return key;
}

//Thêm ticket vào cart để mua
void KhachHangMenu::purchaseTicket(KhachHang &khachHang, LinkedList<Flight> flights)
{
    int soLuongMua, new_soLuongVe;
    std::string ID_chuyenBay;
    std::string request;
    LinkedList<int> IDs;

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
            system("cls");
            std::cout << "Enter information for ticket " << (i + 1) << "/" << soLuongMua << std::endl;
            KhachHang ticket_owner = addNewKhachHang(false);

            IDs.addLast(ticket_owner.getID());

            //tạo giao diện chọn ghế
            std::string selectedSeat = createSeatMapWithIDs(ID_chuyenBay);
            
            // Get ticket from flight's ticket list
            if (currentFlight.tickets.length() > 0) {
                Ticket ticket = currentFlight.tickets.get(i);
                
                // Create new ticket with unique ID and owner
                // Ticket newTicket(ticket.getID_ve(), currentFlight, ticket_owner, ticket.getGhe(), ticket.getgiaVe());
                Ticket newTicket(ticket.getID_ve(), currentFlight, ticket_owner, selectedSeat, ticket.getgiaVe());
                
                ticketsToAdd.addLast(newTicket);
            }
        }

        // Update available tickets
        new_soLuongVe = flight.getsoLuongVe() - soLuongMua;
        updateTicketQuantityInDatabase(ID_chuyenBay, new_soLuongVe);
        
        // Remove used tickets from flight (no more needed)
        // for (int i = 0; i < soLuongMua; i++) {
        //     currentFlight.tickets.removeAtIndex(0);
        // }
        
        // Add all tickets to cart
        for (int i = 0; i < ticketsToAdd.length(); i++) {
            khachHang.getCart().addTickettoCart(ticketsToAdd.get(i));
        } 
        request = getYesNoInput(spaceLineChoice + "Do you want to purchase more tickets? (y/n)");
    } while (request == "y" || request == "Y");
    
    khachHang.purchase(IDs);
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
        
        std::cout<< "Choose [V] to View ticket details by ID \nChoose [B] to Back \nChoose [C] to cancel ticket";
        std::string choice = getStringInput("Enter your choice");
        if (choice == "V" || choice == "v")
        {
            std::string ticketID = getStringInput("Enter the ticket ID you want to view details");
            while (!isValidTicketID(ticketID))
            {
                printError("Invalid ticket ID, please enter again!");
                ticketID = getStringInput("Enter the ticket ID you want to view details");
            }
            std::cout << std::endl;
            // Handle Exception
            std::string recToFind;
            Flight flightToView;
            for (int i = 0; i < khachHang.Rec().length(); i++)  // duyệt qua từng hóa đơn
            {
                LinkedList<std::string> KhachHangIDRecs = getKhachHangIDFromReceipt(khachHang.Rec().get(i));
                LinkedList<std::string> KhachHangTicketIDRecs = getTicketIDFromReceipt(khachHang.Rec().get(i));
                LinkedList<Flight> KhachHangFlightsFromRec = getFlightFromReceipt(khachHang.Rec().get(i));
                for (int j = 0; j < KhachHangFlightsFromRec.length(); j++)
                {
                    if (ticketID == KhachHangTicketIDRecs.get(j))
                    {
                        recToFind = khachHang.Rec().get(i);
                        flightToView = KhachHangFlightsFromRec.get(j);
                    }
                    
                }
            }

            Ticket ticketToView(ticketID , flightToView, khachHang, extractSeatFromTicketID(ticketID), flightToView.getgiaVe(), getIssueDate(recToFind));
            printTicket(khachHang.getID(), ticketToView);
            system("pause");
            orderTicketHistory(khachHang);
        }
        else if (choice == "B" || choice == "b")
        {
            KhachHangMenu::menu(khachHang);
        }
        else if (choice == "C" || choice == "c")
        {
            cancelTicket(khachHang);
        }
        else{
            printError("Invalid choice, please enter again!");
            system("pause");
            orderTicketHistory(khachHang);
        }
    }
}

void KhachHangMenu::cancelTicket(KhachHang &khachHang)
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
    std::string ticketToCancel;
    std::string editRec;
    bool found = false;
    
    for (int i = 0; i < khachHang.Rec().length(); ++i)
    {
        LinkedList<std::string> ticketsID = getTicketIDFromReceipt(khachHang.Rec().get(i));
        for (int j = 0; j < ticketsID.length(); ++j)
        {
            if (ticketsID.get(j) == ticketID)
            {
                ticketToCancel = ticketsID.get(j);
                found = true;
                break;
            }
        }
        if (found)
        {
            editRec = khachHang.Rec().get(i);
            break;
        }
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
        printSuccess("Cancellation aborted.");
        system("pause");
        return;
    }

    // Update ticket availability in the flight's record
    Flight flight = getFlightFromDatabase(extractFlightID(ticketToCancel));
    int updatedQuantity = flight.getsoLuongVe() + 1;
    updateTicketQuantityInDatabase(flight.getID_chuyenBay(), updatedQuantity);

    // Update seat status in the seat map file
    std::string seatNum = extractSeatFromTicketID(ticketToCancel);
    int row = (int)std::floor(std::stoi(seatNum)/8); // Parse row
    int col = std::stoi(seatNum) % 8 - 1;                                  // Parse column
    
    std::string seatFile = flight.getID_chuyenBay() + ".txt";
    std::string seatPath = "./Database/SeatDB/" + seatFile;
    if (!updateSeatStatusInFile(seatPath, row, col, 0))
    {
        printError("Failed to update seat status in file.");
        system("pause");
        return;
    }

    // Remove ticket from the customer's receipts
    removeTicketFromReceipt(editRec, ticketToCancel);

    printSuccess("Ticket canceled successfully!");
    system("pause");
}


LinkedList<std::string> getKhachHangIDFromReceipt(std::string recID)
{
    std::ifstream inFile("./Database/ReceiptDB/" + recID);
    std::string line;
    LinkedList<std::string> customersID;

    // Bỏ qua 2 dòng đầu tiên (thời gian và số hóa đơn)
    getline(inFile, line);
    getline(inFile, line);

    // Đọc các dòng còn lại
    while (getline(inFile, line))
    {
        // Tìm vị trí khoảng trắng để tách ID vé và ID khách hàng
        int spaceIndex = line.find(" ");
        if (spaceIndex == std::string::npos) continue; // Bỏ qua nếu dòng không hợp lệ

        // Tách ID khách hàng (phần sau khoảng trắng)
        std::string ID_khachHang = line.substr(spaceIndex + 1);

        // Thêm ID khách hàng vào danh sách
        customersID.addLast(ID_khachHang);
    }

    inFile.close();
    return customersID;
}

LinkedList<std::string> getTicketIDFromReceipt(std::string recID)
{
    std::ifstream inFile("./Database/ReceiptDB/" + recID);
    std::string line;
    LinkedList<std::string> ticketsID;

    // Bỏ qua 2 dòng đầu tiên (thời gian và số hóa đơn)
    getline(inFile, line);
    getline(inFile, line);

    // Đọc các dòng còn lại
    while (getline(inFile, line))
    {
        // Tìm vị trí khoảng trắng để tách ID vé và ID khách hàng
        int spaceIndex = line.find(" ");
        if (spaceIndex == std::string::npos) continue; // Bỏ qua nếu dòng không hợp lệ

        // Tách ID vé (phần trước khoảng trắng)
        std::string ID_ve = line.substr(0, spaceIndex);

        // Thêm ID vé vào danh sách
        ticketsID.addLast(ID_ve);
    }

    inFile.close();
    return ticketsID;
}

LinkedList<Flight> getFlightFromReceipt(std::string recID)
{
    std::ifstream inFile("./Database/ReceiptDB/" + recID);
    std::string line;
    LinkedList<Flight> flights;

    LinkedList<std::string> TicketIDRecs = getTicketIDFromReceipt(recID);

    // Đọc các dòng còn lại
    for (int i = 0; i < TicketIDRecs.length(); i++)
    {
        std::string ID_ve = TicketIDRecs.get(i);

        int underscoreIndex = ID_ve.find("_");
        if (underscoreIndex == std::string::npos) continue;
        std::string ID_chuyenBay = ID_ve.substr(0, underscoreIndex);
        // Tìm vé theo ID và thêm vào danh sách
        Flight chuyenBay = getFlightFromDatabase(ID_chuyenBay);
        flights.addLast(chuyenBay);
    }

    inFile.close();
    return flights;
}

void getAllKhachHangTickets(KhachHang &KhachHang)
{
    TextTable table;
    int n = KhachHang.Rec().length();
    table.add("Ticket ID");
    table.add("Passenger");
    table.add("Date of departure");
    table.add("Price");
    table.endOfRow();

    int total = 0;
    for (int i = 0; i < n; i++)  // duyệt qua từng hóa đơn
    {
        LinkedList<std::string> KhachHangIDRecs = getKhachHangIDFromReceipt(KhachHang.Rec().get(i));
        LinkedList<std::string> KhachHangTicketIDRecs = getTicketIDFromReceipt(KhachHang.Rec().get(i));
        LinkedList<Flight> KhachHangFlightsFromRec = getFlightFromReceipt(KhachHang.Rec().get(i));
        for (int j = 0; j < KhachHangFlightsFromRec.length(); j++)
        {
            Flight KhachHangFlight = KhachHangFlightsFromRec.get(j);
            table.add(KhachHangTicketIDRecs.get(j));
            table.add(getKhachHangNameFromDatabase(std::stoi(KhachHangIDRecs.get(j))));
            table.add(KhachHangFlight.getngayKhoiHanh());
            table.add(formatCurrency(KhachHangFlight.getgiaVe()));
            table.endOfRow();
            total += KhachHangFlight.getgiaVe();
        }
    }
    table.add("");
    table.add("");
    table.add("Total amount");
    table.add(formatCurrency(total));
    table.endOfRow();

    std::cout << table << std::endl;
}