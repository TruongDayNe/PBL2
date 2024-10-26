#pragma once

#include <iostream>
#include <windows.h>
#include <string>
#include <ctime>
#include <set>
#include <fstream>
#include <algorithm>
#include <conio.h>

using namespace std;

// Get current datetime
// real time
string currentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d-%m-%Y %X", &tstruct);

    return buf;
}