#pragma once

#ifndef CART_H
#define CART_H
#include "../Library/Table.cpp"
#include "../Library/Console.h"

class Ticket;
class Cart
{
private:
    LinkedList<Ticket> ve;
    LinkedList<int> soLuongMua;
    int _Total;

public:
    // Constructor
    Cart();

    // Destructor
    ~Cart();

    // Get list of ticket ID
    LinkedList<Ticket> veMua();

    // Get list of Ticket Quantity
    LinkedList<int> soVeMua();
    int tongsoVeMua();

    // Add ticket to cart
    void addTickettoCart(Ticket, int = 1);

    // Set cart to Null for next purchase
    void emptyCart();

    // Set Total //Calculate total amount (money) in cart
    int Total();
};
#endif