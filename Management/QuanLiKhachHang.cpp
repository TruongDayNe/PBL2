#pragma once
#include "../Business/KhachHang.cpp"
#include "../LinkedList.cpp"
#include "../Library/Console.cpp"
#include "../Library/Table.cpp"
#include "../Menu/KhachHangMenu.cpp"
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>

bool isValidKhachHangID(int KhachHangID)
{
    ifstream inFile("./Database/UserDB/KhachHangDB/KhachHang_ID.txt");
    string x;
    string line;
    while (getline(inFile, x))
    {
        line = x;
        if (stoi(line) == KhachHangID)
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
    string fileName = "KhachHang_" + to_string(KhachHang.getID()) + ".txt";
    string filePath = "./Database/UserDB/KhachHangDB/" + fileName;

    // write KhachHang to database
    ofstream outFile(filePath);
    outFile << KhachHang.getName() << endl;
    outFile << KhachHang.getEmail() << endl;
    outFile << KhachHang.getPassword() << endl;
    for (int i = 0; i < KhachHang.Rec().length(); i++)
    {
        outFile << KhachHang.Rec().get(i) << endl;
    }

    // write KhachHangid to KhachHang_id.txt
    if (!isValidKhachHangID(KhachHang.getID()))
    {
        ofstream outFileKhachHangId("./Database/UserDB/KhachHangDB/KhachHang_ID.txt", ios::app);
        outFileKhachHangId << KhachHang.getID() << endl;
        outFileKhachHangId.close();
    }

    // close ofstream
    outFile.close();
}

KhachHang addNewKhachHang()
{
    cout << spaceLineChoice << "New KhachHang:\n";

    string name = getStringInput("Name");
    string email = getEmailInput();
    while (!isUniqueEmail(email))
    {
        printError("Email already exists, please login instead!");
        system("pause");
        KhachHangMenu::main();
    }
    string pwd = getPasswordInput("Password");

    // create new KhachHang object
    KhachHang khachhang = KhachHang(getLastKhachHangId(), name, email, pwd);

    // save to database
    addKhachHangToDatabase(khachhang);

    ofstream outFile("./Database/UserDB/user_ID.txt", ios::app);
    outFile << khachhang.getID() << " ";
    outFile << khachhang.getEmail() << " ";
    outFile << khachhang.getPassword() << endl;
    outFile.close();

    // update new KhachHang id range
    updateLine("./Database/lastID.txt", 1, getLastKhachHangId());

    return khachhang;
}

KhachHang getKhachHangFromDatabase(int KhachHangID)
{
    // take file path
    // start from main.cpp
    string filePath = "./Database/UserDB/KhachHangDB/";
    string fileName = "KhachHang_" + to_string(KhachHangID) + ".txt";

    ifstream inFile(filePath + fileName);
    string line;

    string name;
    string email;
    string password;

    getline(inFile, line);
    name = line;

    getline(inFile, line);
    email = line;

    getline(inFile, line);
    password = line;

    LinkedList<string> recs;
    while (getline(inFile, line))
    {
        recs.addLast(line);
    }

    return KhachHang(KhachHangID, name, email, password, recs);
}

void deleteKhachHangFromDatabase(int KhachHangID)
{
    KhachHang KhachHang = getKhachHangFromDatabase(KhachHangID);

    string filePath = "./Database/UserDB/KhachHangDB/";
    string fileName = "KhachHang_" + to_string(KhachHangID) + ".txt";

    char char_filePath[(filePath + fileName).length() + 1];
    strcpy(char_filePath, (filePath + fileName).c_str());

    int status = remove(char_filePath);

    if (status == 0)
    {
        printSuccess("Successfully delete this KhachHang!");
        eraseFileLine(filePath + "KhachHang_ID.txt", to_string(KhachHangID));
        eraseFileLine("./Database/UserDB/user_ID.txt", to_string(KhachHangID) + " " + KhachHang.getEmail() + " " + KhachHang.getPassword());
    }
    else
    {
        printError("Delete failed!");
    }
}

void updateKhachHangInDatabase(int KhachHangID)
{
    KhachHang oldKhachHang = getKhachHangFromDatabase(KhachHangID);
    KhachHang KhachHang = getKhachHangFromDatabase(KhachHangID);

    string filePath = "./Database/UserDB/KhachHangDB/";
    string fileName = "KhachHang_" + to_string(KhachHangID) + ".txt";

    char char_filePath[(filePath + fileName).length() + 1];
    strcpy(char_filePath, (filePath + fileName).c_str());

    int status = remove(char_filePath);

    string name = updateComponent("Name", KhachHang.getName());
    string email = updateComponent("Email", KhachHang.getEmail());
    string password = updatePassword(KhachHang.getPassword());

    KhachHang.setID(KhachHangID);
    KhachHang.setName(name);
    KhachHang.setEmail(email);
    KhachHang.setPassword(password);
    KhachHang.setRec(oldKhachHang.Rec());

    addKhachHangToDatabase(KhachHang);
    updateLine("./Database/UserDB/user_ID.txt", to_string(oldKhachHang.getID()) + " " + oldKhachHang.getEmail() + " " + oldKhachHang.getPassword(), to_string(KhachHang.getID()) + " " + KhachHang.getEmail() + " " + KhachHang.getPassword());
}