#ifndef _TOOLS_FUNCTIONS_FUNCTION_H_
#define _TOOLS_FUNCTIONS_FUNCTION_H_

#include <Eigen/Core>

namespace Tools{
  namespace Functions{
    template<class Numeric, size_t inputDim, size_t outputDim>
      class Function{
    public:
      typedef Eigen::Matrix<Numeric, inputDim, 1> InputValue;
      typedef Eigen::Matrix<Numeric, outputDim, 1> OutputValue;
      virtual ~Function(){};
      virtual OutputValue operator()(const InputValue& x) const = 0;  
    };
    template<class Numeric, size_t dim>
      class Function<Numeric, dim, 1>{
    public:
      typedef Eigen::Matrix<Numeric, dim, 1> InputValue;
      typedef Numeric OutputValue;
      virtual ~Function(){};
      virtual OutputValue operator()(const InputValue& x) const = 0;  
    };
    template<class Numeric, size_t dim>
      class Function<Numeric, 1, dim>{
    public:
      typedef Numeric InputValue;
      typedef Eigen::Matrix<Numeric, dim, 1> OutputValue;
      virtual ~Function(){};
      virtual OutputValue operator()(const InputValue& x) const = 0;  
    };
    template<class Numeric>
      class Function<Numeric, 1, 1>{
    public:
      typedef Numeric InputValue;
      typedef Numeric OutputValue;
      virtual ~Function(){};
      virtual OutputValue operator()(const InputValue& x) const = 0;  
    };
  };
};

#endif // _TOOLS_FUNCTIONS_FUNCTION_H_
