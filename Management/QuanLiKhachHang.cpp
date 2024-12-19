#include "QuanLiKhachHang.h"

bool isValidKhachHangID(int KhachHangID)
{
    std::ifstream inFile("./Database/UserDB/KhachHangDB/KhachHang_ID.txt");
    std::string x;
    std::string line;
    while (getline(inFile, x))
    {
        line = x;
        if (std::stoi(line) == KhachHangID)
        {
            return true;
        }
    }
    inFile.close();
    return false;
}

void addKhachHangToDatabase(KhachHang &KhachHang)
{
    // generate file path
    // start from main.cpp
    std::string fileName = "KhachHang_" + std::to_string(KhachHang.getID()) + ".txt";
    std::string filePath = "./Database/UserDB/KhachHangDB/" + fileName;

    // write KhachHang to database
    std::ofstream outFile(filePath);
    outFile << KhachHang.getName() << std::endl;
    outFile << KhachHang.getEmail() << std::endl;
    outFile << KhachHang.getPassword() << std::endl;
    outFile << KhachHang.getCCCD() << std::endl;
    outFile << KhachHang.getMobile() << std::endl;

    //Lưu tên các hóa đơn
    for (int i = 0; i < KhachHang.Rec().length(); i++)
    {
        outFile << KhachHang.Rec().get(i) << std::endl;
    }

    // write KhachHangid to KhachHang_id.txt
    if (!isValidKhachHangID(KhachHang.getID()))
    {
        std::ofstream outFileKhachHangId("./Database/UserDB/KhachHangDB/KhachHang_ID.txt", std::ios::app);
        outFileKhachHangId << KhachHang.getID() << std::endl;
        outFileKhachHangId.close();
    }

    // close ofstream
    outFile.close();
}

KhachHang addNewKhachHang(bool isLogin)
{
    std::cout << spaceLineChoice << "New KhachHang:" << std::endl;

    std::string name = getStringInput("Name");
    std::string email;
    std::string pwd;

    if (isLogin)
    {
        email = getEmailInput();
        while (!isUniqueEmail(email))
        {
            printError("Email already exists, please login instead!");
            system("pause");
            KhachHangMenu::KH_main();
        }
        pwd = getPasswordInput("Password");
    }
    else
    {
        email = "none";
        pwd = "1";
    }

    std::string cccd = getStringInput("CCCD");
    std::string phone = getStringInput("Phone");

    // create new KhachHang object
    KhachHang khachhang = KhachHang(getLastKhachHangId(), name, email, pwd, cccd, phone);

    // save to database
    addKhachHangToDatabase(khachhang);

    std::ofstream outFile("./Database/UserDB/user_ID.txt", std::ios::app);
    outFile << khachhang.getID() << " ";
    outFile << khachhang.getEmail() << " ";
    outFile << khachhang.getPassword() << " ";
    outFile << khachhang.getCCCD() << " ";
    outFile << khachhang.getMobile() << std::endl;
    outFile.close();

    // update new KhachHang id range
    updateLine("./Database/lastID.txt", 1, getLastKhachHangId());

    return khachhang;
}

KhachHang getKhachHangFromDatabase(int KhachHangID)
{
    // take file path
    // start from main.cpp
    std::string filePath = "./Database/UserDB/KhachHangDB/";
    std::string fileName = "KhachHang_" + std::to_string(KhachHangID) + ".txt";

    std::ifstream inFile(filePath + fileName);
    std::string line;

    std::string name;
    std::string email;
    std::string password;
    std::string cccd;
    std::string phone;

    getline(inFile, line);
    name = line;

    getline(inFile, line);
    email = line;

    getline(inFile, line);
    password = line;

    getline(inFile, line);
    cccd = line;

    getline(inFile, line);
    phone = line;

    LinkedList<std::string> recs;
    while (getline(inFile, line))
    {
        recs.addLast(line);
    }

    return KhachHang(KhachHangID, name, email, password, cccd, phone, recs);
}

void deleteKhachHangFromDatabase(int KhachHangID)
{
    KhachHang KhachHang = getKhachHangFromDatabase(KhachHangID);

    std::string filePath = "./Database/UserDB/KhachHangDB/";
    std::string fileName = "KhachHang_" + std::to_string(KhachHangID) + ".txt";

    char char_filePath[(filePath + fileName).length() + 1];
    strcpy(char_filePath, (filePath + fileName).c_str());

    int status = remove(char_filePath);

    if (status == 0)
    {
        printSuccess("Successfully delete this KhachHang!");
        eraseFileLine(filePath + "KhachHang_ID.txt", std::to_string(KhachHangID));
        eraseFileLine("./Database/UserDB/user_ID.txt", std::to_string(KhachHangID) + " " + KhachHang.getEmail() + " " + KhachHang.getPassword() + " " + KhachHang.getCCCD() + " " + KhachHang.getMobile());
    }
    else
    {
        printError("Delete failed!");
    }
}

void updateKhachHangInDatabase(int KhachHangID)
{
    KhachHang oldkhachHang = getKhachHangFromDatabase(KhachHangID);
    KhachHang khachHang = getKhachHangFromDatabase(KhachHangID);

    std::string filePath = "./Database/UserDB/KhachHangDB/";
    std::string fileName = "KhachHang_" +std:: to_string(KhachHangID) + ".txt";

    char char_filePath[(filePath + fileName).length() + 1];
    strcpy(char_filePath, (filePath + fileName).c_str());

    int status = remove(char_filePath);

    std::string name = updateComponent("Name", khachHang.getName());
    std::string email = updateComponent("Email", khachHang.getEmail());
    std::string cccd = updateComponent("CCCD", khachHang.getCCCD());
    std::string phone = updateComponent("Phone", khachHang.getMobile());
    std::string password = updatePassword(khachHang.getPassword());

    khachHang.setID(KhachHangID);
    khachHang.setName(name);
    khachHang.setEmail(email);
    khachHang.setPassword(password);
    khachHang.setCCCD(cccd);
    khachHang.setMobile(phone);
    khachHang.setRec(oldkhachHang.Rec());

    addKhachHangToDatabase(khachHang);

    std::ofstream outFile("./Database/UserDB/user_ID.txt", std::ios::app);
    outFile << khachHang.getID() << " ";
    outFile << khachHang.getEmail() << " ";
    outFile << khachHang.getPassword() << " ";
    outFile << khachHang.getCCCD() << " ";
    outFile << khachHang.getMobile() << std::endl;
    outFile.close();

    updateLine("./Database/UserDB/user_ID.txt",
    std::to_string(oldkhachHang.getID()) + " " + oldkhachHang.getEmail() + " " + oldkhachHang.getPassword() + " " + oldkhachHang.getCCCD() + " " + oldkhachHang.getMobile(),
    std::to_string(khachHang.getID()) + " " + khachHang.getEmail() + " " + khachHang.getPassword() + " " + khachHang.getCCCD() + " " + khachHang.getMobile());
}

void printKhachHang(KhachHang &khachHang)
{
    TextTable table;

    table.add("Name");
    table.add("Email");
    table.add("CCCD");
    table.add("Mobile");  
    table.endOfRow();

    table.add(khachHang.getName());
    table.add(khachHang.getEmail());
    table.add(khachHang.getCCCD());
    table.add(khachHang.getMobile());
    table.endOfRow();

    std::cout << table << std::endl;
}