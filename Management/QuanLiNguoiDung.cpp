#include "QuanLiNguoiDung.h"
#include "../Menu/KhachHangMenu.h"

User getUserLoginInfo(std::string info)
{
    std::string id, email, password, cccd, phone;

    // Tìm vị trí của từng dấu cách
    int firstIndex = info.find(" ");
    int secondIndex = info.find(" ", firstIndex + 1);
    int thirdIndex = info.find(" ", secondIndex + 1);
    int fourthIndex = info.find(" ", thirdIndex + 1);

    // // Kiểm tra chuỗi có đủ 5 phần tử hay không
    // if (firstIndex == std::string::npos || secondIndex == std::string::npos || 
    //     thirdIndex == std::string::npos || fourthIndex == std::string::npos) {
    //     throw std::invalid_argument("Invalid input format");
    // }

    // Tách các phần tử
    id = info.substr(0, firstIndex);
    email = info.substr(firstIndex + 1, secondIndex - firstIndex - 1);
    password = info.substr(secondIndex + 1, thirdIndex - secondIndex - 1);
    cccd = info.substr(thirdIndex + 1, fourthIndex - thirdIndex - 1);
    phone = info.substr(fourthIndex + 1);

    // Trả về đối tượng User với 5 tham số
    return User(std::stoi(id), email, password, cccd, phone);
}

LinkedList<User> getAllUserLoginInfo()
{
    LinkedList<User> usersInfo;

    std::ifstream inFile("./Database/UserDB/user_ID.txt");
    if (!inFile.is_open())
    {
        printError("Error in open user info file database!");
        return usersInfo;
    }

    std::string x;
    while (getline(inFile, x))
    {
        usersInfo.addLast(getUserLoginInfo(x));
    }

    inFile.close();
    return usersInfo;
}

int findUser(std::string email, std::string password)
{
    LinkedList<User> users = getAllUserLoginInfo();

    for (int i = 0; i < users.length(); i++)
    {
        User user = users.get(i);
        if (user.getEmail() == email && user.getPassword() == password)
        {
            return user.getID();
        }
    }
    return -1;
}