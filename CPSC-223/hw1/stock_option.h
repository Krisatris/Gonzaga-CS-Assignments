//----------------------------------------------------------------------
// Author: Stella Beemer
// Assignment: 1
//
// A basic stock option class, which adds a sell (put) strike price to
// a stock. Note the purchase price for an option is the cost of the
// contract. The strike price is the amount an underlying share of the
// stock can be sold for. A profit is made if the current stock price
// is below the strike price less the cost of the contract.
// ----------------------------------------------------------------------

#ifndef STOCK_OPTION_H
#define STOCK_OPTION_H

#include <string>
#include "stock.h"

class StockOption : public Stock
{
public:
  // crate a stock option with the given symbol
  StockOption(std::string the_symbol);

  // set the strike price per share
  void set_strike_price(double the_strike_price);

  // strike price per share
  double get_strike_price() const;

  // the net worth of the option
  double sell_value() const;

private:
  double strike_price = 0;      // price to sell per holding
};

#endif
