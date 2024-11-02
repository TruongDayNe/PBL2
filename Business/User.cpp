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

User::~User()
{
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

void User::searchByTicketID()
{
    searchByTicketsID();
}

void User::printAllTicket()
{
    printAllTickets();
}
