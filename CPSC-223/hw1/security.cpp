//----------------------------------------------------------------------
// Author: Stella Beemer
// Assignment: 1
//----------------------------------------------------------------------

#include <string>
#include "security.h"

Security::Security(std::string the_symbol) : symbol(the_symbol)
{}


std::string Security::get_symbol() const
{
  return symbol;
}


void Security::set_share_value(double current_share_value)
{
  share_value = current_share_value;
}


double Security::get_share_value() const
{
  return share_value;
}


void Security::set_holdings(int number_of_holdings)
{
  holdings = number_of_holdings;
}


int Security::get_holdings() const
{
  return holdings;
}


double Security::market_worth() const
{
  return get_share_value() * get_holdings();
}
