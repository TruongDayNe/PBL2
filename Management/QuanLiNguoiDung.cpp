#include "QuanLiNguoiDung.h"

User getUserLoginInfo(std::string info)
{
    std::string id;
    std::string email;
    std::string password;

    int firstIndex = info.find_first_of(" ");
    int lastIndex = info.find_last_of(" ");

    id = info.substr(0, firstIndex);
    email = info.substr(firstIndex + 1, lastIndex - firstIndex - 1);
    password = info.substr(lastIndex + 1, info.length() - lastIndex);

    return User(stoi(id), email, password);
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