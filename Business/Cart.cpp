#pragma once
#include "Cart.h"
#include "../Management/QuanLiVe.cpp"
#include "../Library/Table.cpp"
#include "../Library/Console.cpp"

Cart::Cart()
{
    this->_Total = 0;
}

Cart::~Cart()
{
}

LinkedList<int> Cart::ID_veMua()
{
    return this->ID_ve;
}

LinkedList<int> Cart::soVeMua()
{
    return this->soLuongMua;
}

int Cart::Total()
{
    int total = 0;
    for (int i = 0; i < this->ID_ve.length(); i++)
    {
        Ticket Ve = getTicketFromDatabase(this->ID_ve.get(i));
        total += Ve.getgiaVe() * this->soLuongMua.get(i);
    }
    return total;
}

void Cart::addTickettoCart(int id, int quantity)
{
    this->ID_ve.addLast(id);
    this->soLuongMua.addLast(quantity);
}

void Cart::emptyCart()
{
    this->ID_ve = LinkedList<int>();
    this->soLuongMua = LinkedList<int>();
    this->_Total = 0;
}