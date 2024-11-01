
#pragma once
#include "User.h"
#include "LinkedList.h"

class Admin : public User {
public:
    Admin();
    ~Admin();
    void updateTicketInDatabase(int); 
    void addNewTicketToDataBase();
    void deleteTicketFromDatabase(int);
    void addNewReceipt();
    void searchByReceiptID(int);
    void deleteReceiptById(string);
};