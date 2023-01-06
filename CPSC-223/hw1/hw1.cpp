//----------------------------------------------------------------------
// Author: Stella Beemer
// Assignment: 1
//
// Basic test file for securities, stocks, and stock options
//----------------------------------------------------------------------

#include <iostream>
#include <assert.h>
#include "security.h"
#include "stock.h"
#include "stock_option.h"

using namespace std;

// returns true if stock value is positive
bool should_sell(const Stock& the_stock);

int main(int argc, char** argv)
{
  Security s1("GOOG");
  s1.set_share_value(1245);
  s1.set_holdings(120);
  assert(s1.get_share_value() == 1245);
  assert(s1.get_holdings() == 120);
  assert(s1.market_worth() == 1245*120);

  Stock s2("APPL");
  s2.set_share_value(204);
  s2.set_holdings(76);
  s2.set_purchase_price(175);
  assert(s2.get_share_value() == 204);
  assert(s2.get_holdings() == 76);
  assert(s2.get_purchase_price() == 175);
  assert(s2.market_worth() == 204*76);
  assert(s2.sell_value() == (204-175)*76);

  StockOption s3("AMZN");
  s3.set_share_value(1823);
  s3.set_holdings(500);
  s3.set_purchase_price(5.25);
  s3.set_strike_price(1828);
  assert(s3.get_share_value() == 1823);
  assert(s3.get_holdings() == 500);
  assert(s3.get_purchase_price() == 5.25);
  assert(s3.get_strike_price() == 1828);
  assert(s3.market_worth() == 1823*500);
  assert(s3.sell_value() == (1828-5.25)*500 - 1823*500);
  
  assert(should_sell(s2) == true);
  assert(should_sell(s3) == false);
}


bool should_sell(const Stock& the_stock)
{
  return the_stock.sell_value() > 0;
}
