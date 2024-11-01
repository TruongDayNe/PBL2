#pragma once

#include "../LinkedList.h"
#include "Ticket.h"
#include "../Management/QuanLiVe.h"
#include "../Library/Table.cpp"
#include "../Library/Console.h"

#ifndef CART_H
#define CART_H

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
#endif