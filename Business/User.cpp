#include "User.h"

User::User()
{
    this->_ID = 0;
    this->_Name = "";
    this->_Email = "";
    this->_Password = "";
}

User::User(int id, std::string name)
{
    this->_ID = id;
    this->_Name = name;
}

User::User(int id, std::string email, std::string password)
{
    this->_ID = id;
    this->_Email = email;
    this->_Password = password;
}

User::User(int id, std::string name, std::string email, std::string password)
{
    this->_ID = id;
    this->_Name = name;
    this->_Email = email;
    this->_Password = password;
}

User::User(int id, std::string email, std::string password, std::string cccd, std::string phone)
{
    this->_ID = id;
    this->_Email = email;
    this->_Password = password;
    this->_CCCD = cccd;
    this->_Mobile = phone;
}

User::User(int id, std::string name, std::string email, std::string password, std::string cccd, std::string phone)
{
    this->_ID = id;
    this->_Name = name;
    this->_Email = email;
    this->_Password = password;
    this->_CCCD = cccd;
    this->_Mobile = phone;
}

User::~User()
{
}

// Toán tử gán
User& User::operator=(const User& other) {
    if (this != &other) { // Kiểm tra tự gán
        this->_ID = other._ID;               // Sao chép ID
        this->_Name = other._Name;           // Sao chép Name
        this->_Email = other._Email;         // Sao chép Email
        this->_Password = other._Password;   // Sao chép Password
    }
    return *this; // Trả về đối tượng hiện tại
}

int User::getID()
{
    return this->_ID;
}

void User::setID(int id)
{
    this->_ID = id;
}

std::string User::getName()
{
    return this->_Name;
}

void User::setName(std::string name)
{
    this->_Name = name;
}

std::string User::getEmail()
{
    return this->_Email;
}

void User::setEmail(std::string email)
{
    this->_Email = email;
}

std::string User::getPassword()
{
    return this->_Password;
}

void User::setPassword(std::string password)
{
    this->_Password = password;
}

std::string User::getCCCD()
{
    return this->_CCCD;
}

void User::setCCCD(std::string cccd)
{
    this->_CCCD = cccd;
}

std::string User::getMobile()
{
    return this->_Mobile;
}

void User::setMobile(std::string mobile)
{
    this->_Mobile = mobile;
}

// void User::searchByTicketID()
// {
//     searchByTicketsID();
// }

// void User::printAllTicket()
// {
//     printAllTickets();
// }
