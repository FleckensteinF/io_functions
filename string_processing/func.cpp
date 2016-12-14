#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <algorithm>
#include <limits>
#include <vector>

#include "func.h"

/// test double values for equality
/**
   \param a first of the values to be compared 
   \param b second of the values to be compared
   \param epsilon maximal difference allowed for the values to be considered equal. defaults to 3 * the double precision limit.
   \return true if a=b, false otherwise
 */
bool Tools::StringProcessing::eq_d(double a, double b, double epsilon){
  return (bool)(fabs(a-b) < epsilon);
}

/// round floats & doubles to arbitrary precision
/**
   \param d floating point number to be rounded
   \param n number of digits accepted (defaults to 0)
   \returns rounded floating point number
*/
double Tools::StringProcessing::round(double d, unsigned int n){
  return ((double)((int)(d*pow(10,n)+0.5)))/pow(10,n);
}

/// round floats & doubles to multiples of arbitrary floats
double Tools::StringProcessing::roundTo(double d, double s){
  return ((double)((int)(d/s+0.5)))*s;
}

/// tests if a number lies within a range
/** if the range is inverted (i.e. from larger to smaller)  the result is inverted as well (i.e. NOT in Range [b,a])
    \param x value to be tested
    \param a lower interval limit
    \param b upper interval limit
    \return true if x in [a,b] or b<a and x not in [a,b], 
 */
bool Tools::StringProcessing::inRange(double x, double a, double b){
  if(a<b) return (bool)((a<x) && (x<b));
  else return (bool)((x<b) || (a<x));
}

/// get absolute integer value
/**
  \param n integer value (positive or negative)
  \return |n| (absolute value of n, always positive)
*/
int Tools::StringProcessing::abs(int n){
  if(n>0) return n;
  return (-n);
}
