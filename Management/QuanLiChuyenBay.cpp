#include "QuanLiChuyenBay.h"

// bool isValidFlightId(std::string flightID)
// {
//     std::ifstream inFile("./Database/Airports.txt");
//     std::string x;
//     while (getline(inFile, x))
//     {
//         if (x == flightID)
//         {
//             return true;
//         }
//     }
//     inFile.close();
//     return false;
// }
bool isValidFlightID(const std::string& flightID)
{
    std::ifstream inFile("./Database/FlightDB/flights.csv");
    if (!inFile.is_open()) {
        throw std::runtime_error("Không thể mở file flights.csv");
    }

    std::string line, currentFlightID;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::getline(ss, currentFlightID, ','); // Lấy mã chuyến bay
        if (currentFlightID == flightID) {
            inFile.close();
            return true;
        }
    }
    inFile.close();
    return false;
}

void addFlightToDatabase(Flight &flight)
{
    // generate file path
    // start from main.cpp
    //std::string fileName = std::to_string(flight.getID_chuyenBay()) + ".txt";
    std::string filePath = "./Database/FlightDB/flights.csv";

    // create file in database
    std::ofstream outFile(filePath, std::ios::app);
    // outFile << computer.ID() << endl;
    outFile << flight.getID_chuyenBay() + ",";
    outFile << flight.getdiemDi() + ",";
    outFile << flight.getdiemDen() + ",";
    outFile << flight.getngayKhoiHanh() + ",";
    outFile << flight.getsoLuongVe() + ",";
    outFile << flight.getgiaVe() + "," << std::endl;

    // if (!isValidFlightId(flight.getID_chuyenBay()))
    // {
    //     std::ofstream outFileTicketId("./Database/TicketDB/ticket_ID.txt", std::ios::app);
    //     outFileTicketId << flight.getID_chuyenBay() << std::endl;
    //     outFileTicketId.close();
    // }


    // close ofstream
    outFile.close();
}

void addNewFlightToDataBase()
{
    std::cout << spaceLineChoice + "New flight:\n";
    std::string ID_chuyenBay = getStringInput("ID chuyến bay");
    std::string diemDi = getStringInput("Điểm đi");
    std::string diemDen = getStringInput("Điểm đến");
    std::string ngayKhoiHanh = getStringInput("Ngày giờ khởi hành (dd-mm-yy hh:mm:ss)");
    unsigned int soLuongVe = getIntInput("Số lượng vé");
    int giaVe = getIntInput("Giá vé");
    // Create new Ticket object
    Flight flight = Flight(ID_chuyenBay, diemDi, diemDen, ngayKhoiHanh, soLuongVe, giaVe );

    // Save to database
    addFlightToDatabase(flight);

    // Update new Ticket id range
    //updateLine("./Database/lastID.txt", 0, updateLastTicketId());

    // // Generate sale and write to sale file
    // ofstream outFilesale("./Database/saleSummary.txt", ios::app);
    // outFilesale << ticket.getID_ve() << " " << ticket.getsoGhe() << endl;
    // outFilesale.close();
}

// Flight getFlightFromDatabase(std::string flightID)
// {
//     //std::string fileName = std::to_string(ticketID) + ".txt";
//     std::string filePath = "./Database/FlightDB/flights.csv";

//     std::ifstream inFile(filePath);
//     std::string line;
//     std::string ID_chuyenBay;
//     std::string diemDi;
//     std::string diemDen;
//     std::string ngayKhoiHanh;
//     int soLuongVe;
//     int giaVe;


//     getline(inFile, line);
//     ticketID = std::stoi(line);

//     getline(inFile, line);
//     ID_chuyenBay = line;

//     getline(inFile, line);
//     diemDi = line;

//     getline(inFile, line);
//     diemDen = line;

//     getline(inFile, line);
//     ngayKhoiHanh = line;

//     getline(inFile, line);
//     soLuongVe = std::stoi(line);

//     getline(inFile, line);
//     giaVe = std::stoi(line);

//     return  Ticket(updateLastTicketId(), ID_chuyenBay, diemDi, diemDen, loaiVe, ngayKhoiHanh, soLuongVe, giaVe);
// }
Flight getFlightFromDatabase(std::string flightID)
{
    std::ifstream inFile("./Database/FlightDB/flights.csv");
    if (!inFile.is_open()) {
        throw std::runtime_error("Không thể mở file");
    }

    std::string line;
    std::string ID_chuyenBay;
    std::string diemDi;
    std::string diemDen;
    std::string ngayKhoiHanh;
    std::string soLuongVe_str;
    std::string giaVe_str;
    
    bool found = false;
    while(getline(inFile, line)) {
        std::stringstream ss(line);
        getline(ss, ID_chuyenBay, ',');
        getline(ss, diemDi, ',');
        getline(ss, diemDen, ',');
        getline(ss, ngayKhoiHanh, ',');
        getline(ss, soLuongVe_str, ',');
        getline(ss, giaVe_str, ',');
        
        if (ID_chuyenBay == flightID) {
            found = true;
            break;
        }
    }

    if (!found) {
        throw std::runtime_error("Không tìm thấy vé với ID này");
    }

    int soLuongVe = std::stoi(soLuongVe_str);
    int giaVe = std::stoi(giaVe_str);

    inFile.close();
    return Flight(ID_chuyenBay, diemDi, diemDen, ngayKhoiHanh, soLuongVe, giaVe);
}
void deleteFlightFromDatabase(std::string flightID)
{
    std::string filePath = "./Database/FlightDB/flight.csv";

    // char char_filePath[(filePath + fileName).length() + 1];
    // strcpy(char_filePath, (filePath + fileName).c_str());

    //int status = remove((filePath + fileName).c_str());

    try
    {
        printSuccess("Succesfully delete this Ticket!");
        eraseFileLine(filePath, findLine("./Database/FlightDB/flight.csv",flightID));
        //eraseFileLine("./Database/saleSummary.txt", ticketID);
    }
    catch (const std::exception& e) {
        throw std::invalid_argument("Lỗi: " + std::string(e.what()));
        printError("Delete failed!");
    }
}

void updateFlightInDatabase(std::string flightID)
{
    Flight flight = getFlightFromDatabase(flightID);
    std::string filePath = "./Database/FlightDB/flights.csv";

    char char_filePath[(filePath).length() + 1];
    strcpy(char_filePath, (filePath).c_str());

    int status = remove(char_filePath);

    std::string ID_chuyenBay = updateComponent("ID chuyến bay", flight.getID_chuyenBay());
    std::string diemDi = updateComponent("Điểm đi", flight.getdiemDi());
    std::string diemDen = updateComponent("Điểm đến", flight.getdiemDen());
    std::string ngayKhoiHanh = updateComponent("Ngày khởi hành (dd-mm-yy hh:mm:ss)", flight.getngayKhoiHanh());
    int soLuongVe = updateIntComponent("Số lượng vé", flight.getsoLuongVe());
    int giaVe = updateIntComponent("Giá vé", flight.getgiaVe());

    flight.setID_chuyenBay(ID_chuyenBay);
    flight.setdiemDi(diemDi);
    flight.setdiemDen(diemDen);
    flight.setngayKhoiHanh(ngayKhoiHanh);
    flight.setsoLuongVe(soLuongVe);
    flight.setgiaVe(giaVe);

    addFlightToDatabase(flight);
    printSuccess("Succesfully update!");
}

LinkedList<Flight> getAllFlight() //fix
{
    LinkedList<Flight> flights;

    std::ifstream inFile("./Database/FlightDB/flights.csv");
    if (!inFile.is_open())
    {
        printError("Error open file ticket_ID.txt");
    }
    std::string x;

    // Create a new Ticket object
    // Get each Ticket from database then add it to the list of Tickets
    while (getline(inFile, x))
    {
        std::istringstream ss(x); // Dùng stringstream để phân tích chuỗi
        std::string flightID;
        if (getline(ss, flightID, ',')) // Lấy mã vé
        {
            Flight flight = getFlightFromDatabase(flightID);
            flights.addLast(flight);
        }
    }

    inFile.close();
    return flights;
}

void printFlight(Flight flight)
{
    TextTable table;

    table.add("Flight Number");
    table.add("Departure");
    table.add("Arrival");
    table.add("Departure Time");
    table.add("Seats");
    table.add("Price(VND)");
    table.endOfRow();

    table.add(flight.getID_chuyenBay());
    table.add(flight.getdiemDi());
    table.add(flight.getdiemDen());
    table.add(flight.getngayKhoiHanh());
    table.add(std::to_string(flight.getsoLuongVe()));
    table.add(formatCurrency(flight.getgiaVe()));
    table.endOfRow();

    std::cout << table << std::endl;
}

void printAllFlights(LinkedList<Flight> flights)
{

    TextTable table;

    table.add("Flight Number");
    table.add("Departure");
    table.add("Arrival");
    table.add("Departure Time");
    table.add("Seats");
    table.add("Price(VND)");
    table.endOfRow();

    for (int i = 0; i < flights.length(); i++)
    {
        Flight flight = flights.get(i);
        table.add(flight.getID_chuyenBay());
        table.add(flight.getdiemDi());
        table.add(flight.getdiemDen());
        table.add(flight.getngayKhoiHanh());
        table.add(std::to_string(flight.getsoLuongVe()));
        table.add(formatCurrency(flight.getgiaVe()));
        table.endOfRow();
    }

    std::cout << table << std::endl;
}

void searchByFlightsID()
{
    std::string id = getStringInput("Enter ID");
    if (!isValidFlightID(id))
    {
        printError("Invalid ID, please enter again!");
    }
    else
    {
        Flight flight = getFlightFromDatabase(id);
        printFlight(flight);
    }
}

LinkedList<Flight> searchByFlightCase(std::string StarttoSearch, std::string EndtoSearch)
{
    LinkedList<Flight> res;
    LinkedList<Flight> flights = getAllFlight();

    for (int i = 0; i < flights.length(); i++)
    {
        if (findCaseInsensitive(flights.get(i).getdiemDi(), StarttoSearch) != std::string::npos &&
            findCaseInsensitive(flights.get(i).getdiemDen(), EndtoSearch) != std::string::npos)
        {
            res.addLast(flights.get(i));
        }
    }
    return res;
}

LinkedList<Flight> searchByFlightsPath()
{
    std::string diemDi = getStringInput("Điểm đi: ");
    std::string diemDen = getStringInput("Điểm đến: ");
    LinkedList<Flight> flights = searchByFlightCase(diemDi, diemDen);

    if (flights.length())
    {
        printSuccess("Tìm thấy vé!");
        return flights;
    }
    else
    {
        return LinkedList<Flight>();
    }
}
// void updateFlightQuantityInDatabase(std::string id, int quantity)
// {
//     if (quantity == 0)
//     {
//         deleteFlightFromDatabase(id);
//         return;
//     }
//     updateLine("./Database/FlighetDB/flights.csv", 6, quantity);
// }
void updateTicketQuantityInDatabase(const std::string& flightID, int quantity)
{
    std::string filePath = "./Database/FlightDB/flights.csv";
    std::string tempFilePath = "./Database/FlightDB/temp_flights.csv";

    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        throw std::runtime_error("Không thể mở file flights.csv");
    }

    std::ofstream outFile(tempFilePath);
    if (!outFile.is_open()) {
        throw std::runtime_error("Không thể tạo file tạm temp_flights.csv");
    }

    std::string line;
    bool found = false;

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string currentFlightID, diemDi, diemDen, ngayKhoiHanh, soLuongVeStr, giaVeStr;

        // Lấy thông tin từng cột
        std::getline(ss, currentFlightID, ',');
        std::getline(ss, diemDi, ',');
        std::getline(ss, diemDen, ',');
        std::getline(ss, ngayKhoiHanh, ',');
        std::getline(ss, soLuongVeStr, ',');
        std::getline(ss, giaVeStr, ',');

        // Nếu tìm thấy chuyến bay cần sửa, ghi lại với số lượng vé mới
        if (currentFlightID == flightID) {
            found = true;
            outFile << currentFlightID << "," << diemDi << "," << diemDen << "," 
                    << ngayKhoiHanh << "," << quantity << "," << giaVeStr << "\n";
        } else {
            // Ghi lại dòng không thay đổi
            outFile << line << "\n";
        }
    }

    inFile.close();
    outFile.close();

    // Kiểm tra xem chuyến bay đã được tìm thấy hay chưa
    if (!found) {
        std::remove(tempFilePath.c_str()); // Xóa file tạm nếu không có thay đổi
        throw std::runtime_error("Không tìm thấy mã chuyến bay để cập nhật");
    }

    if (std::remove(filePath.c_str()) != 0) {
    throw std::runtime_error("Không thể xóa file flights.csv trước khi ghi đè");
    }
    // Ghi đè file gốc bằng file tạm
    if (std::rename(tempFilePath.c_str(), filePath.c_str()) != 0) {
        throw std::runtime_error("Lỗi khi ghi đè file flights.csv");
    }
}
