#pragma once
#include <iostream>
#include <fstream>
#include "../Library/Console.h"
#include "../Library/MenuBox.h"
#include "KhachHangMenu.h"
#include "AdminMenu.h"

class Home
{
public:
    static void welcome();
    static int printTask();
    // static void login();
    // static void signUp();
    static void menu();
};
