#include "Console.h"

std::string spaceLine = "\t\t         ";
std::string spaceLineChoice = "\t    ";
// Get current datetime
// real time
// Hàm lấy thời gian hiện tại dưới dạng chuỗi
std::string currentDateTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d-%m-%Y %X", &tstruct);
    return buf;
}

// Hàm chuyển đổi chuỗi thời gian thành time_t
time_t convertToTimeT(const std::string& dateTime) {
    struct tm t = {};
    std::istringstream ss(dateTime);
    ss >> std::get_time(&t, "%d-%m-%Y %H:%M:%S");
    return mktime(&t);
}

// Hàm so sánh thời gian hiện tại với thời gian đầu vào
bool isExpired(const std::string& dateTime) {
    return (difftime(time(0), convertToTimeT(dateTime)) > 0.0);
}

// Change text color in terminal
void printLineColor(std::string line, int color_code)
{
    HANDLE color;
    color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, color_code);
    std::cout << line;
    SetConsoleTextAttribute(color, 7);
}
// Get input with string type
std::string getStringInput(std::string title)
{
    std::string value;

    printLineColor(spaceLineChoice + title + ": ", 6);
    std::getline(std::cin, value);

    return value;
}
// Get input with int type
int getIntInput(std::string title)
{
    std::string value;
    printLineColor(spaceLineChoice + title + ": ", 6);
    std::getline(std::cin, value);

    while (!isNumber(value))
    {
        printError("Invalid value!");
        printLineColor(spaceLineChoice + title + ": ", 6);
        std::getline(std::cin, value);
    }

    return std::stoi(value);
}
// Check if string s is a number
bool isNumber(std::string s)
{
    char *end = nullptr;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && *end == '\0';
}
void printError(std::string status)
{
    std::cout << spaceLineChoice;
    printLineColor(" ERROR ", 67);
    printLineColor(" " + status, 4);
    std::cout << std::endl;
}
int updateLastTicketId()
{
    std::ifstream inFile("./Database/lastID.txt");

    std::string x;
    getline(inFile, x);

    return std::stoi(x) + 1;
}
// Get input with yes/no
std::string getYesNoInput(std::string title)
{
    std::string yn;

    printLineColor(title + ": ", 3);
    std::getline(std::cin, yn);

    while (yn != "y" && yn != "Y" && yn != "n" && yn != "N")
    {
        printError("You must enter a valid value (y/n)!");
        printLineColor(title + ": ", 3);
        std::getline(std::cin, yn);
    }

    return yn;
}
std::string updateComponent(std::string key, std::string value)
{
    std::string update;

    printLineColor(spaceLineChoice + key + ": ", 6);
    printLineColor(value + "\n", 7);
    update = getYesNoInput(spaceLineChoice + "Update " + key + " (y/n)");

    std::string newValue = value;
    if (update == "y" || update == "Y")
    {
        newValue = getStringInput("New " + key);
    }

    return newValue;
}

// Update int component with y/n
int updateIntComponent(std::string key, int value)
{
    std::string update;

    printLineColor(spaceLineChoice + key + ": ", 6);
    printLineColor(std::to_string(value) + "\n", 7);
    update = getYesNoInput(spaceLineChoice + "Update " + key + " (y/n)");

    int newValue = value;
    if (update == "y" || update == "Y")
    {
        newValue = getIntInput("New " + key);
    }

    return newValue;
}
// Update line input in file
// path: path to file in database, start from main.cpp file
// numLine: index of line, start from 0
// replaceValue: new line value
void updateLine(std::string path, int numLine, int replaceValue)
{
    std::string line;
    std::ifstream fin;

    fin.open(path);
    std::ofstream temp;
    temp.open("temp.txt");
    int count = 0;

    while (getline(fin, line))
    {
        if (count == numLine)
        {
            temp << replaceValue << std::endl;
            count++;
            continue;
        }
        temp << line << std::endl;
        count++;
    }

    temp.close();
    fin.close();

    const char *p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}

// Update line input in file
// path: path to file in database, start from main.cpp file
// inLine: line to update
// replaceValue: new line value
void updateLine(std::string path, std::string inLine, std::string replaceValue)
{
    std::string line;
    std::ifstream fin;

    fin.open(path);
    if (!fin.is_open())
    {
        printError("Eror open file" + path);
    }
    std::ofstream temp;
    temp.open("temp.txt");

    while (getline(fin, line))
    {
        if (line == inLine)
        {
            temp << replaceValue << std::endl;
            continue;
        }
        temp << line << std::endl;
    }

    temp.close();
    fin.close();

    const char *p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}
// Print notification
void printSuccess(std::string status)
{
    std::cout << spaceLineChoice;
    printLineColor(" SUCCESS ", 37);
    printLineColor(" " + status, 2);
    std::cout << std::endl;
}
// Delete line input from file
// path: path to file in database
// start from main.cpp file
// eraseLine: line to delete
void eraseFileLine(std::string path, std::string eraseLine)
{
    std::ifstream fin(path);
    std::ofstream temp("temp.txt");

    std::string line;
    while (getline(fin, line))
    {
        // Kiểm tra nếu dòng không phải là dòng cần xóa
        if (line != eraseLine)
        {
            temp << line << "\n";
        }
    }

    temp.close();
    fin.close();

    // Ghi lại nội dung file tạm vào file gốc
    const char *p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}


// Delete line input from file
// path: path to file in database
// start from main.cpp file
// eraseLine: line contain int item to delete
void eraseFileLine(std::string path, int eraseLine)
{
    std::string line;
    int firstIndex;
    std::ifstream fin;

    fin.open(path);
    std::ofstream temp;
    temp.open("temp.txt");

    while (std::getline(fin, line))
    {
        firstIndex = line.find_first_of(" ");
        if (line.substr(0, firstIndex) != std::to_string(eraseLine))
            temp << line << std::endl;
    }

    temp.close();
    fin.close();

    const char *p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}
// Format int
std::string formatInt(int num)
{
    std::string s = std::to_string(num);
    std::string ans = "";
    for (int i = s.length() - 1; i >= 0; i -= 3)
    {
        if (i > 2)
        {
            std::string sub = s.substr(i - 3 + 1, 3);
            ans = sub + ans;
            ans = "," + ans;
        }
        else
        {
            std::string sub = s.substr(0, i + 1);
            ans = sub + ans;
        }
    }
    return ans;
}

std::string formatCurrency(int price)
{
    return formatInt(price) + " VND";
}
// Find position of a piece of data in a string
// case insensitive
// data: string
// toSearch: string need to search
// pos: start position to search in data
size_t findCaseInsensitive(std::string data, std::string toSearch, size_t pos)
{
    transform(data.begin(), data.end(), data.begin(), ::tolower);
    transform(toSearch.begin(), toSearch.end(), toSearch.begin(), ::tolower);
    return data.find(toSearch, pos);
}
// Check if string email is valid email form
bool isEmail(std::string email)
{
    int dot = -1, at = -1;
    for (int i = email.length() - 1; i >= 0; --i)
    {
        if (email[i] == '@')
        {
            at = i;
        }
        if (email[i] == '.')
        {
            dot = i;
        }
    }
    if (dot != -1 && at != -1 && at < dot)
    {
        return true;
    }
    return false;
}
std::string getEmailInput()
{
    std::string email;
    printLineColor(spaceLineChoice + "Email: ", 6);
    std::getline(std::cin, email);

    while (!isEmail(email))
    {
        printError("Invalid email!");
        printLineColor(spaceLineChoice + "Email: ", 6);
        std::getline(std::cin, email);
    }

    return email;
}

std::string getPasswordInput(std::string title)
{
    printLineColor(spaceLineChoice + title + ": ", 6);
    std::string pwd = "";
    char a = getch();
    while (a != 10 && a != 13)
    {
        if (a != 8)
        {
            std::cout << '*';
            pwd += a;
            a = getch();
        }
        else if (pwd.length() > 0)
        {
            std::cout << "\b \b";
            pwd = pwd.erase(pwd.size() - 1);
            a = getch();
        }
        else
        {
            a = getch();
        }
    }

    std::cout << std::endl;
    return pwd;
}

LinkedList<std::string> getAllEmail()
{
    LinkedList<std::string> list;
    std::set<std::string> emails;

    std::ifstream inFile("./Database/UserDB/user_ID.txt");
    std::string line;
    int first, last;

    while (std::getline(inFile, line))
    {
        first = line.find_first_of(" ");
        last = line.find_last_of(" ");

        std::string email = line.substr(first + 1, last - first - 1);
        emails.insert(email);
    }

    std::set<std::string>::iterator it;
    for (it = emails.begin(); it != emails.end(); ++it)
    {
        std::string mail = *it;
        list.addLast(mail);
    }

    inFile.close();
    return list;
}

bool isUniqueEmail(std::string emailToCheck)
{
    LinkedList<std::string> emails = getAllEmail();
    for (int i = 0; i < emails.length(); i++)
    {
        std::string email = emails.get(i);
        if (emailToCheck == email)
        {
            return false;
        }
    }
    return true;
}

int getLastKhachHangId()
{
    std::ifstream inFile("./Database/lastID.txt");

    std::string x;
    std::getline(inFile, x);
    std::getline(inFile, x);
    return std::stoi(x) + 1;
}

// FIXED so it won't use lastID.txt
// int getLastKhachHangId()    
// {
//     std::ifstream inFile("./Database/KhachHang_ID.txt");
//     if (!inFile) {
//         std::cerr << "Error opening file.\n";
//         return -1; // Return error code if file cannot be opened
//     }

//     std::string line, id;
//     int maxId = 0; // Initialize maxId to 0

//     while (getline(inFile, line)) {
//         std::stringstream ss(line);
//         getline(ss, id, ' '); // Extract the first column (ID)

//         if (!id.empty()) {
//             int currentId = std::stoi(id);
//             maxId = std::max(maxId, currentId); // Update maxId if currentId is larger
//         }
//     }

//     return maxId;
// }

std::string getReceiptDateTime(int patientID, std::string recID)
{
    std::ifstream inFile("./Database/ReceiptDB/" + std::to_string(patientID) + "_" + recID + ".txt");

    std::string x;
    std::getline(inFile, x);

    return x;
}

int getReceiptTotal(int patientID, std::string recID)
{
    std::ifstream inFile("./Database/ReceiptDB/" + std::to_string(patientID) + "_" + recID + ".txt");

    std::string x;
    std::getline(inFile, x);
    std::getline(inFile, x);

    return std::stoi(x);
}

// Update price
// old_price: current price
int updatePrice(int old_price)
{
    printLineColor(spaceLineChoice + "Price: ", 6);
    printLineColor(std::to_string(old_price) + "\n", 7);
    int new_price = old_price;

    std::string yn = getYesNoInput(spaceLineChoice + "Update Price (y/n)");

    if (yn == "y" || yn == "Y")
    {
        new_price = getIntInput("Price");
    }

    return new_price;
}

// Update password
// old_pass: current password value
std::string updatePassword(std::string old_pass)
{
    std::string yn = getYesNoInput(spaceLineChoice + "Update Password (y/n)");

    if (yn == "n" || yn == "N")
    {
        return old_pass;
    }

    std::string old_pass_input = getPasswordInput("Enter old password");

    while (old_pass != old_pass_input)
    {
        printError("Wrong password!");
        old_pass_input = getPasswordInput("Enter old password");
    }

    std::string new_password = getPasswordInput("Enter new password");

    return new_password;
}

std::string trim(const std::string& str) {
    // Find the first non-space character
    auto start = std::find_if_not(str.begin(), str.end(), [](unsigned char c) { return std::isspace(c); });
    // Find the last non-space character
    auto end = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char c) { return std::isspace(c); }).base();
    
    // Return the trimmed string
    return (start < end) ? std::string(start, end) : std::string();
}

int findLine(const std::string& filename, const std::string& targetLine) {
    std::ifstream file(filename); // Open the file
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    int index = 0;

    // Read the file line by line
    while (std::getline(file, line)) {
        if (line == targetLine) {
            return index; // Return the index if the line matches
        }
        index++;
    }

    return -1; // Return -1 if the line is not found
}

std::string getDateFromString(const std::string &dateTime)
{
    // Chuỗi định dạng: "DD-MM-YYYY HH:MM:SS"
    size_t spacePos = dateTime.find(' ');
    if (spacePos == std::string::npos)
    {
        throw std::invalid_argument("Invalid date-time format: " + dateTime);
    }
    return dateTime.substr(0, spacePos); // Trả về phần ngày: "DD-MM-YYYY"
}

std::string getTimeFromString(const std::string &dateTime)
{
    // Chuỗi định dạng: "DD-MM-YYYY HH:MM:SS"
    size_t spacePos = dateTime.find(' ');
    if (spacePos == std::string::npos)
    {
        throw std::invalid_argument("Invalid date-time format: " + dateTime);
    }
    return dateTime.substr(spacePos + 1); // Trả về phần giờ: "HH:MM:SS"
}

// Hàm chuyển đổi ID vé thành ID chuyến bay
std::string extractFlightID(const std::string& ticketID) {
    size_t pos = ticketID.find('_'); // Tìm vị trí của ký tự '_'
    if (pos != std::string::npos) {
        return ticketID.substr(0, pos); // Lấy phần từ đầu đến trước '_'
    }
    return ""; // Trả về chuỗi rỗng nếu không tìm thấy '_'
}

std::string extractNumbers(const std::string& input) {
    std::string result;
    for (char ch : input) {
        if (std::isdigit(ch)) { // Kiểm tra nếu ký tự là số
            result += ch;       // Thêm ký tự số vào kết quả
        }
    }
    return result;
}


bool taoSoDoGhe(int soGhe, const std::string& ID_chuyenBay) {
    // Kiểm tra số ghế hợp lệ
    if (soGhe <= 0) {
        std::cerr << "Error: Số ghế phải lớn hơn 0.\n";
        return false;
    }

    const int soCot = 8; // Cố định 8 cột (ABCDEFGH)
    int soDong = (soGhe + soCot - 1) / soCot; // Tính số dòng, làm tròn lên

    // Cấp phát bộ nhớ động cho ma trận ghế
    int** maTranGhe = new int*[soDong];
    for (int i = 0; i < soDong; ++i) {
        maTranGhe[i] = new int[soCot];
    }

    // Khởi tạo ma trận ghế
    for (int i = 0; i < soDong; ++i) {
        for (int j = 0; j < soCot; ++j) {
            maTranGhe[i][j] = 0; // Mặc định tất cả ghế là trống
        }
    }

    // Đánh dấu các ghế không tồn tại (ở dòng cuối, nếu có)
    int soGheThua = soDong * soCot - soGhe; // Số ghế dư trong ma trận
    for (int i = 0; i < soGheThua; ++i) {
        maTranGhe[soDong - 1][soCot - 1 - i] = -1; // Ghế không tồn tại
    }

    // Tạo tên file
    std::string fileName = "./Database/SeatDB/" + ID_chuyenBay + ".txt";

    // Mở file để ghi
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Không thể mở file " << fileName << " để ghi.\n";

        // Giải phóng bộ nhớ
        for (int i = 0; i < soDong; ++i) {
            delete[] maTranGhe[i];
        }
        delete[] maTranGhe;

        return false;
    }

    // Ghi ma trận ghế vào file
    for (int i = 0; i < soDong; ++i) {
        for (int j = 0; j < soCot; ++j) {
            if (maTranGhe[i][j] == -1) {
                file << "x "; // Ghế không tồn tại
            } else {
                file << maTranGhe[i][j] << " "; // Ghế bình thường
            }
        }
        file << "\n"; // Xuống dòng sau mỗi hàng
    }

    file.close();

    // Giải phóng bộ nhớ
    for (int i = 0; i < soDong; ++i) {
        delete[] maTranGhe[i];
    }
    delete[] maTranGhe;

    std::cout << "Đã tạo thành công sơ đồ ghế cho chuyến bay: " << ID_chuyenBay << std::endl;
    return true;
}


int getSeatIndex(const std::string& seatCode) {
    // Kiểm tra tính hợp lệ của mã ghế
    if (seatCode.length() < 2 || 
        !isdigit(seatCode[0]) || 
        !isupper(seatCode[1]) || 
        seatCode[1] < 'A' || seatCode[1] > 'H') {
        return -1; // Mã ghế không hợp lệ
    }

    int row = std::stoi(seatCode.substr(0, 1)) - 1; // Chuyển hàng về chỉ số 0
    int col = seatCode[1] - 'A'; // Chuyển cột về chỉ số 0

    return row * 8 + col + 1; // Tính toán chỉ số thứ tự
}

std::string extractSeatFromTicketID(const std::string& ticketID) {
    size_t pos = ticketID.find('_'); // Tìm vị trí của ký tự '_'
    if (pos != std::string::npos) {
        return ticketID.substr(pos + 1); // Lấy phần từ sau '_'
    }
    return ""; // Trả về chuỗi rỗng nếu không tìm thấy '_'
}

std::string getIssueDate(const std::string& recID){
    std::ifstream inFile("./Database/ReceiptDB/" + recID);
    std::string line;
    std::getline(inFile, line);
    return line;
}
