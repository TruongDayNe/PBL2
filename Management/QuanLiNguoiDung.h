#pragma once

#include "../Business/User.h"
#include <string>
#include <fstream>
#include "../LinkedList.h"

// Function prototypes
User getUserLoginInfo(std::string info);
int findUser(std::string email, std::string password);
LinkedList<User> getAllUserLoginInfo();
