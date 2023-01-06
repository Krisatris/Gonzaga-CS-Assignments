// ----------------------------------------------------------------------
// Author: Stella Beemer
// Assignment: 2
// ----------------------------------------------------------------------

#include "decimal.h"
#include <iostream>

// default value is "0."
Decimal::Decimal() : point_loc(0)
{
  digits.push_back(0);
}

// two argument constructor
Decimal::Decimal(std::string val, int point_location)
  : point_loc(point_location)
{
  int n = int(val.size());
  // invalid cases: bad point location, empty string
  if (point_loc > n || n == 0) {
    // set to default value "0."
    point_loc = 0;
    digits.push_back(0);
    return;
  }
  // parse string
  for (int i = 0; i < n; ++i) {
    char c = val[i];
    if (std::isdigit(c))
      digits.push_back(c - '0');
    else {
      // invalid character found
      digits.clear();
      point_loc = 0;
      digits.push_back(0);
      return;
    }
  }
  reduce_zeros();
}

// overloaded plus operator
Decimal Decimal::operator+(const Decimal& rhs) const 
{
  // create vector copies for adding
  int_vec lhs_copy = digits;
  int_vec rhs_copy = rhs.digits;
  Decimal final = Decimal();

  // add zeroes to end of vector with least decimal points
  int i;
  if(point_loc > rhs.point_loc) 
  {
    final.point_loc = point_loc;
    for(i = 0; i < (point_loc - rhs.point_loc); ++i)
      rhs_copy.push_back(0);
  } else 
  {
    final.point_loc = rhs.point_loc;
    for(i = 0; i < (rhs.point_loc - point_loc); ++i)
      lhs_copy.push_back(0);
  }

  // add zeroes to beginning of vector to make size equal
  int j;
  int size_diff = 0;
  if(lhs_copy.size() > rhs_copy.size())
  {
    size_diff = lhs_copy.size() - rhs_copy.size();
    for(j = 0; j < size_diff; ++j)
      rhs_copy.insert(rhs_copy.begin(), 0);
  } else if(rhs_copy.size() > lhs_copy.size())
  {
    size_diff = rhs_copy.size() - lhs_copy.size();
    for(j = 0; j < size_diff; ++j)
      lhs_copy.insert(lhs_copy.begin(), 0);
  }

  // add the vectors
  int_vec result_vec;
  int result = 0;
  int overflow = 0;
  int k;
  for(k = rhs_copy.size() - 1; k > -1; --k) {
    result = lhs_copy.at(k) + rhs_copy.at(k) + overflow;
    overflow = 0;
    if(result > 9) {
      result -= 10;
      overflow = 1;
    }
    result_vec.insert(result_vec.begin(), result); 
    result = 0;
    if(k == 0 && overflow > 0)
      result_vec.insert(result_vec.begin() + 0, 1); 
  }
  final.digits = result_vec;
  final.reduce_zeros();
  return final;
}

// prefix increment operator overload
Decimal& Decimal::operator++() 
{
  *this = *this + Decimal("1", 0);
  return *this;
}

// postfix increment operator overload
Decimal Decimal::operator++(int) 
{
  Decimal copy = *this;
  *this = *this + Decimal("1", 0);
  return copy;
}

// less than operator overload
bool Decimal::operator<(const Decimal& rhs) const
{
  int lhs_rational = digits.size() - point_loc;
  int rhs_rational = rhs.digits.size() - rhs.point_loc;
  if(lhs_rational < rhs_rational)
    return true;
  else if(rhs_rational < lhs_rational) 
    return false;
  else 
  {
    int unsigned smallest;
    if(digits.size() > rhs.digits.size())
      smallest = rhs.digits.size();
    else 
      smallest = digits.size();
    int unsigned i;
    for(i = 0; i < smallest; ++i) 
    {
      if(digits.at(i) < rhs.digits.at(i))
        return true;
      else if(rhs.digits.at(i) < digits.at(i))
        return false;
    }
    if(digits.size() < rhs.digits.size())
      return true;
    return false;
  }
}

// equal to operator overload
bool Decimal::operator==(const Decimal& rhs) const
{
  return !(*this < rhs) && !(rhs < *this);
}

// greater than operator overload
bool Decimal::operator>(const Decimal& rhs) const 
{
  return !(*this < rhs) && !(*this == rhs);
}

// less than or equal to operator overload
bool Decimal::operator<=(const Decimal& rhs) const
{
  return !(rhs < *this);
}

// greater than or equal to operator overload
bool Decimal::operator>=(const Decimal& rhs) const
{
  return !(*this < rhs);
}

// not equal to operator overload
bool Decimal::operator!=(const Decimal& rhs) const 
{
  return !(*this == rhs);
}

// print operator overload
std::ostream& operator<<(std::ostream& out, const Decimal& val) {
  for(int i = 0; i < val.digits.size(); ++i) {
    if(i == (val.digits.size() - val.point_loc))
      out << ".";
    out << val.digits.at(i);
  }
  return out;
}

// private function that removes unecessairy zeroes from beginning and end
void Decimal::reduce_zeros() 
{
  while(digits.back() == 0 && point_loc > 0)
  {
    digits.pop_back();
    --point_loc;
  }
  int length = digits.size();
  while(digits.at(0) == 0 && point_loc != length) 
  {
    digits.erase(digits.begin());
  }
}
