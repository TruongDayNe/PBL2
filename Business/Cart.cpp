#include "Cart.h"
#include "Ticket.h"

Cart::Cart()
{
    this->_Total = 0;
}

Cart::~Cart()
{
}

LinkedList<Ticket> Cart::veMua()
{
    return this->ve;
}

LinkedList<int> Cart::soVeMua()
{
    return this->soLuongMua;
}

int Cart::tongsoVeMua()
{
    int sovemua;
    for (int i = 0; i < this->ve.length(); i++)
    {
        sovemua += (this->soLuongMua.get(i));
    }
    return sovemua;
}

int Cart::Total()
{
    int total = 0;
    for (int i = 0; i < this->ve.length(); i++)
    {
        int giaVe = ve.get(i).getgiaVe();
        total += giaVe * this->soLuongMua.get(i);
    }
    return total;
}

void Cart::addTickettoCart(Ticket ticket, int quantity)
{
    this->ve.addLast(ticket);
    this->soLuongMua.addLast(quantity);
}

void Cart::emptyCart()
{
    this->ve = LinkedList<Ticket>();
    this->soLuongMua = LinkedList<int>();
    this->_Total = 0;
}