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

string spaceLine = "\t\t         ";
string spaceLineChoice = "\t    ";
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
// Change text color in terminal
void printLineColor(string line, int color_code)
{
    HANDLE color;
    color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, color_code);
    cout << line;
    SetConsoleTextAttribute(color, 7);
}
// Get input with string type
string getStringInput(string title)
{
    string value;

    printLineColor(spaceLineChoice + title + ": ", 6);
    getline(cin, value);

    return value;
}
// Get input with int type
int getIntInput(string title)
{
    string value;
    printLineColor(spaceLineChoice + title + ": ", 6);
    getline(cin, value);

    while (!isNumber(value))
    {
        printError("Invalid value!");
        printLineColor(spaceLineChoice + title + ": ", 6);
        getline(cin, value);
    }

    return stoi(value);
}
// Check if string s is a number
bool isNumber(string s)
{
    char *end = nullptr;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && *end == '\0';
}
void printError(string status)
{
    cout << spaceLineChoice;
    printLineColor(" ERROR ", 67);
    printLineColor(" " + status, 4);
    cout << endl;
}
int updateLastTicketId()
{
    ifstream inFile("./Database/lastID.txt");

    string x;
    getline(inFile, x);

    return stoi(x) + 1;
}
// Get input with yes/no
string getYesNoInput(string title)
{
    string yn;

    printLineColor(title + ": ", 3);
    getline(cin, yn);

    while (yn != "y" && yn != "Y" && yn != "n" && yn != "N")
    {
        printError("You must enter a valid value (y/n)!");
        printLineColor(title + ": ", 3);
        getline(cin, yn);
    }

    return yn;
}
string updateComponent(string key, string value)
{
    string update;

    printLineColor(spaceLineChoice + key + ": ", 6);
    printLineColor(value + "\n", 7);
    update = getYesNoInput(spaceLineChoice + "Update " + key + " (y/n)");

    string newValue = value;
    if (update == "y" || update == "Y")
    {
        newValue = getStringInput("New " + key);
    }

    return newValue;
}

// Update int component with y/n
int updateIntComponent(string key, int value)
{
    string update;

    printLineColor(spaceLineChoice + key + ": ", 6);
    printLineColor(to_string(value) + "\n", 7);
    update = getYesNoInput(spaceLineChoice + "Update " + key + " (y/n)");

    int newValue = value;
    if (update == "y" || update == "Y")
    {
        newValue = getIntInput("New " + key);
    }

    return newValue;
}
// Update line input in file
// path: path to file in database, start from main.cpp file
// numLine: index of line, start from 0
// replaceValue: new line value
void updateLine(string path, int numLine, int replaceValue)
{
    string line;
    ifstream fin;

    fin.open(path);
    ofstream temp;
    temp.open("temp.txt");
    int count = 0;

    while (getline(fin, line))
    {
        if (count == numLine)
        {
            temp << replaceValue << endl;
            count++;
            continue;
        }
        temp << line << endl;
        count++;
    }

    temp.close();
    fin.close();

    const char *p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}

// Update line input in file
// path: path to file in database, start from main.cpp file
// inLine: line to update
// replaceValue: new line value
void updateLine(string path, string inLine, string replaceValue)
{
    string line;
    ifstream fin;

    fin.open(path);
    if (!fin.is_open())
    {
        printError("Eror open file" + path);
    }
    ofstream temp;
    temp.open("temp.txt");

    while (getline(fin, line))
    {
        if (line == inLine)
        {
            temp << replaceValue << endl;
            continue;
        }
        temp << line << endl;
    }

    temp.close();
    fin.close();

    const char *p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}
// Print notification
void printSuccess(string status)
{
    cout << spaceLineChoice;
    printLineColor(" SUCCESS ", 37);
    printLineColor(" " + status, 2);
    cout << endl;
}
// Delete line input from file
// path: path to file in database
// start from main.cpp file
// eraseLine: line to delete
void eraseFileLine(string path, string eraseLine)
{
    string line;
    ifstream fin;

    fin.open(path);
    ofstream temp;
    temp.open("temp.txt");

    while (getline(fin, line))
    {
        if (line != eraseLine)
            temp << line << endl;
    }

    temp.close();
    fin.close();

    const char *p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}

// Delete line input from file
// path: path to file in database
// start from main.cpp file
// eraseLine: line contain int item to delete
void eraseFileLine(string path, int eraseLine)
{
    string line;
    int firstIndex;
    ifstream fin;

    fin.open(path);
    ofstream temp;
    temp.open("temp.txt");

    while (getline(fin, line))
    {
        firstIndex = line.find_first_of(" ");
        if (line.substr(0, firstIndex) != to_string(eraseLine))
            temp << line << endl;
    }

    temp.close();
    fin.close();

    const char *p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}
// Format int
string formatInt(int num)
{
    string s = to_string(num);
    string ans = "";
    for (int i = s.length() - 1; i >= 0; i -= 3)
    {
        if (i > 2)
        {
            string sub = s.substr(i - 3 + 1, 3);
            ans = sub + ans;
            ans = "," + ans;
        }
        else
        {
            string sub = s.substr(0, i + 1);
            ans = sub + ans;
        }
    }
    return ans;
}

string formatCurrency(int price)
{
    return formatInt(price) + " VND";
}
// Find position of a piece of data in a string
// case insensitive
// data: string
// toSearch: string need to search
// pos: start position to search in data
size_t findCaseInsensitive(string data, string toSearch, size_t pos = 0)
{
    transform(data.begin(), data.end(), data.begin(), ::tolower);
    transform(toSearch.begin(), toSearch.end(), toSearch.begin(), ::tolower);
    return data.find(toSearch, pos);
}
// Check if string email is valid email form
bool isEmail(string email)
{
    int dot = -1, at = -1;
    for (int i = email.length() - 1; i >= 0; --i)
    {
        if (email[i] == '@')
        {
            at = i;
        }
        if (email[i] == '.')
        {
            dot = i;
        }
    }
    if (dot != -1 && at != -1 && at < dot)
    {
        return true;
    }
    return false;
}
string getEmailInput()
{
    string email;
    printLineColor(spaceLineChoice + "Email: ", 6);
    getline(cin, email);

    while (!isEmail(email))
    {
        printError("Invalid email!");
        printLineColor(spaceLineChoice + "Email: ", 6);
        getline(cin, email);
    }

    return email;
}

string getPasswordInput(string title)
{
    printLineColor(spaceLineChoice + title + ": ", 6);
    string pwd = "";
    char a = getch();
    while (a != 10 && a != 13)
    {
        if (a != 8)
        {
            cout << '*';
            pwd += a;
            a = getch();
        }
        else if (pwd.length() > 0)
        {
            cout << "\b \b";
            pwd = pwd.erase(pwd.size() - 1);
            a = getch();
        }
        else
        {
            a = getch();
        }
    }

    cout << endl;
    return pwd;
}