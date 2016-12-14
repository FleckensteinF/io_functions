#ifndef _TOOLS_FUNCTIONS_FUNCTION_LOOKUP_H_
#define _TOOLS_FUNCTIONS_FUNCTION_LOOKUP_H_

#include "function.h"

namespace Tools{
  namespace Functions{
    template<class Numeric>
      class FunctionLookup : public Function<Numeric, 1, 1>{
    public:
      typedef typename Function<Numeric, 1, 1>::OutputValue OutputValue;
      typedef typename Function<Numeric, 1, 1>::InputValue InputValue;
      virtual OutputValue operator()(const InputValue& x) const;
    protected:
      std::vector<Numeric> _values;
      Numeric _minX, _maxX;
      Numeric _intervallSize, _intervallSizeInverse;
    };
  };
};

#include "function_lookup.hpp"

#endif // _TOOLS_FUNCTIONS_FUNCTION_LOOKUP_H_
