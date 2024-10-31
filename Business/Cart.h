#pragma once
#include "./LinkedList.cpp"
#include "./Ticket.h"
#include "./Ticket.cpp"

class Cart
{
private:
    LinkedList<int> ID_ve;
    LinkedList<int> soLuongMua;
    int _Total;

public:
    // Constructor
    Cart();

    // Destructor
    ~Cart();

    // Get list of drug ID
    LinkedList<int> ID_veMua();

    // Get list of drug Quantity
    LinkedList<int> soVeMua();

    // Add drug to cart
    void addTickettoCart(int, int = 1);

    // Set cart to Null for next purchase
    void emptyCart();

    // Set Total //Calculate total amount (money) in cart
    int Total();
};