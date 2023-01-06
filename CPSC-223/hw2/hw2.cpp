// ----------------------------------------------------------------------
// Author: Stella Beemer
// Assignment: 2
//
// Basic driver for testing the Decimal class implementation using
// assert statements. This file only partially tests the Decimal class
// and should be extended (see TODO below) with your own test cases.
// ----------------------------------------------------------------------


#include <iostream>
#include <cassert>
#include "decimal.h"

using namespace std;


int main(int argc, char** argv)
{
  // poorly formed decimal values
  Decimal zero = Decimal();
  assert(Decimal("", 0) == zero);
  assert(Decimal("123", 4) == zero);

  // increment
  Decimal one = Decimal("1", 0);
  assert(++Decimal() == one);
  assert(Decimal()++ == zero);

  // basic addition
  Decimal x = Decimal("12345", 1);
  Decimal y = Decimal("67890", 3);
  assert(x + y == Decimal("1302390", 3));

  // large addition
  Decimal z = Decimal("99999999999999999999", 5);
  z = z + Decimal("00001", 5);
  assert(z == Decimal("100000000000000000000", 5));
  
  // test same values
  Decimal pi_1("314159", 5);
  Decimal pi_2("3141590", 6);
  assert(pi_1 == pi_2);
  assert(!(pi_1 != pi_2));
  assert(!(pi_1 < pi_2));
  assert(!(pi_1 > pi_2));
  assert(pi_1 <= pi_2);
  assert(pi_1 >= pi_2);
  
  // test printing
  cout << "should be 1: " << Decimal("1",0) << endl;
  cout << "should be 43: " << Decimal("430", 1) << endl;
  cout << "should be 1.75: " << Decimal("01750", 3) << endl;

  cout << "attempting x + y " << (x + y) << endl;

  Decimal x_a("4206", 1);
  Decimal x_b("42069", 2);
  assert(x_a < x_b);

  Decimal x_d("42183", 2);
  Decimal x_e("5791429", 1);
  assert(x_d < x_e);

  Decimal x_f("18005882300", 5);
  Decimal x_g("8008008533", 2);
  Decimal x_h("49012491247412894812941912840124812", 10);
  Decimal x_i("180058823", 3);

  assert(!(x_f >= x_h));
  assert(x_h > (x_f + x_g));
  assert(x_g < x_h);
  assert(!(x_f != x_i));

  cout << x_h << endl;
  cout << x_f << endl;

  x_f++;
  ++x_h;

  assert(x_f == Decimal("18005982300", 5));
  assert(x_h == Decimal("49012491247412894812941922840124812", 10));
}

