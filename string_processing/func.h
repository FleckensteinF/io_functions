#ifndef _FUNC_H_
#define _FUNC_H_

namespace Tools{
  namespace StringProcessing{
    // number analysis functions

    bool inRange(double x, double a, double b);
    bool eq_d(double a, double b, double epsilon = 10*std::numeric_limits<double>::epsilon());

    // number modification functions

    int abs(int n);
    double round(double d, unsigned int n);
    double roundTo(double d, double s);
  };
};
#endif // _FUNC_H_
