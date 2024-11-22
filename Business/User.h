#pragma once

#include <iostream>
#include <string>

#ifndef USER_H
#define USER_H

class User
{
private:
    int _ID;
    std::string _Name;
    std::string _Email;
    std::string _Password;
    std::string _CCCD;
    std::string _Mobile;

public:
    // Constructor
    User();
    User(int, std::string);
    User(int, std::string, std::string);
    User(int, std::string, std::string, std::string);
    User(int, std::string, std::string, std::string, std::string);
    User(int, std::string, std::string, std::string, std::string, std::string);

    // Destructor
    ~User();

    User& operator=(const User& other);

    // Get, Set User _Id
    int getID();
    void setID(int);

    // Get, Set User _Name
    std::string getName();
    void setName(std::string);

    // Get, Set User _Email
    std::string getEmail();
    void setEmail(std::string);

    // Get, Set User _Password
    std::string getPassword();
    void setPassword(std::string);

    std::string getCCCD();
    void setCCCD(std::string);

    std::string getMobile();
    void setMobile(std::string);

    void searchByTicketID();
    // void searchByDrugName();
    void printAllTicket();
};
#endif