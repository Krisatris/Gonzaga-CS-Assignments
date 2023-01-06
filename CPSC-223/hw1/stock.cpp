//----------------------------------------------------------------------
// Author: Stella
// Assignment: 1
//----------------------------------------------------------------------

#include "stock.h"

Stock::Stock(std::string the_symbol) : Security(the_symbol)
{}

void Stock::set_purchase_price(double the_purchase_price)
{
  purchase_price = the_purchase_price;
}

double Stock::get_purchase_price() const
{
  return purchase_price;
}

double Stock::sell_value() const
{
  return (get_share_value() - purchase_price) * get_holdings();
}

