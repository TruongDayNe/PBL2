#include "AdminMenu.h"

void AdminMenu::AD_main()
{
    system("cls");
    // std::ifstream inFile("./PBL2/Menu/AdminMenu.txt");
    // std::string line;
    // while (getline(inFile, line))
    // {
    //     std::cout << line << std::endl;
    // }
    // inFile.close();
    char data[200][200] = {
        "\t   Login",
        "\t   Back",
    };
    MenuBox MENU(2, data);
    int key = MENU.menu();
    switch (key)
    {
    case 1:
    {
        AdminMenu::login();
        system("pause");
        break;
    }

    case 2:
        Home::menu();
        break;
    }
}
void AdminMenu::login()
{
    system("cls");

    const std::string ADMIN_USERNAME = "admin";
    const std::string ADMIN_PASSWORD = "admin123";
    int attempts = 3;

    do
    {
        std::cout << "\n\t\t=== ADMIN LOGIN ===\n";
        std::cout << "\t\t-------------------\n";

        std::string username;
        std::cout << "\tUsername: ";
        std::cin >> username;

        std::string password = getPasswordInput("Password");

        if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD)
        {
            printSuccess("Login successful!");
            system("pause");
            AdminMenu::menu(); // Chuyển đến menu admin
            return;
        }
        else
        {
            attempts--;
            if (attempts > 0)
            {
                printError("Invalid username/password. " + std::to_string(attempts) + " attempts remaining.");
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

void AdminMenu::menu()
{
    system("cls");
    std::string flightID;    
    while (true)
    {
        int key = AdminMenu::printTask();
        switch (key)
        {
        case 1:
        {    
            //get all flights
            LinkedList<Flight> flights = getAllFlight();
            if (flights.length() == 0)
            {
                printError("Không có chuyến bay nào");
                AdminMenu::menu();
                break;
            }
            printAllFlights(flights);
            system("pause");
            AdminMenu::menu();
        }
        case 2:
        {    
            //searchbyPath
            LinkedList<Flight> flights = searchByFlightsPath();
            printAllFlights(flights);
            flightID = getStringInput("Nhập mã chuyến bay bạn muốn chỉnh sửa");
            if (!isValidFlightID(flightID))
            {
                printError("Mã chuyến bay không hợp lệ");
                AdminMenu::menu();
                break;
            }
        }
        case 3:
        {    
            addNewFlightToDataBase();
            printSuccess("Thêm chuyến bay thành công");
            AdminMenu::menu();
            break;
        }
        case 4:
        {    
            Home::menu();
            break;
        }
        default:
            break;
        }
    }
}

int AdminMenu::printTask()
{
    system("cls");
    std::ifstream inFile("./Page/AdminMenu.txt");
    std::string line;
    while (getline(inFile, line))
    {
        std::cout << line << std::endl;
    }
    inFile.close();

    char data[200][200] =
        {
            "\t  Xem thông tin tất cả chuyến bay",
            "\t  Tìm chuyến bay để chỉnh sửa",
            "\t  Thêm chuyến bay",
            "\t  Đăng xuất",
        };

    MenuBox MENU(4, data);
    int key = MENU.menu();
    return key;
}