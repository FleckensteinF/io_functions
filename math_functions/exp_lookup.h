#ifndef _TOOLS_FUNCTIONS_EXP_LOOKUP_H_
#define _TOOLS_FUNCTIONS_EXP_LOOKUP_H_

#include "function_lookup.h"

namespace Tools{
  namespace Functions{
    class ExpForGaussian : public FunctionLookup<double>{
    public:
      static ExpForGaussian expLookup;
      ExpForGaussian();
    };
  };
};


#endif // _TOOLS_FUNCTIONS_EXP_LOOKUP_H_
