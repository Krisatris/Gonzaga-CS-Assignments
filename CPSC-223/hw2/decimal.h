// ----------------------------------------------------------------------
// Author: Stella Beemer
// Assignment: 2
//
// Class definition for the Decimal class, which can be used to
// represent arbitrarily large non-negative rational numbers. Decimal
// objects can be added, incremented, and compared (using standard
// relational comparators). 
// ----------------------------------------------------------------------


#ifndef DECIMAL_H
#define DECIMAL_H

#include <string>
#include <vector>
#include <iostream>


typedef std::vector<int> int_vec; // int is really too big (for 0 to 9)


class Decimal
{
public:
  
  // default (no-arg) constructor, defaults to value (0.)
  Decimal();                    
  // overloaded constructor, set to given string value (of all digits)
  Decimal(std::string val, int point_location);
  
  // binary addition operator
  Decimal operator+(const Decimal& rhs) const;
  // prefix increment operator
  Decimal& operator++();
  // postfix increment operator
  Decimal operator++(int);  
  
  // six relational comparison operators
  bool operator<(const Decimal& rhs) const;
  bool operator==(const Decimal& rhs) const;  
  bool operator>(const Decimal& rhs) const;
  bool operator<=(const Decimal& rhs) const;
  bool operator>=(const Decimal& rhs) const;
  bool operator!=(const Decimal& rhs) const;  
  
  // to print a Decimal number
  friend std::ostream& operator<<(std::ostream& out, const Decimal& val);
  
private:

  // helper function to remove leading and trailing zeros
  void reduce_zeros();

  // creates int from vector

  int_vec digits;  // list from most to least significant digits
  int point_loc;   // location of the decimal point from least sig digit
  
};


#endif
