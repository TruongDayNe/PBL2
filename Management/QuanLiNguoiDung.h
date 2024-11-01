#pragma once

#include "D:/Code/PBL2/Business/User.h"

#include <string>
#include <fstream>

// Function prototypes
User getUserLoginInfo(std::string info);
LinkedList<User> getAllUserLoginInfo();
int findUser(std::string email, std::string password);
