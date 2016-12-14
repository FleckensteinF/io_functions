#ifndef _TOOLS_INTEGRAL_LOOKUP_H_
#define _TOOLS_INTEGRAL_LOOKUP_H_

#include "integral.h"

namespace Tools{
  namespace Integral{
    template<class Numeric>
      class IntegralLookup1D : public IntegralOverFunction<Numeric, 1>{
    public:
      typedef typename IntegralOverFunction<Numeric, 1>::InputValue InputValue;
      typedef typename IntegralOverFunction<Numeric, 1>::FunctionType FunctionType;
      IntegralLookup1D(FunctionType const* function,  const InputValue& minValue, const InputValue& maxValue, const Numeric& intervallSize);
      Numeric integrate(const InputValue& minValue, const InputValue& maxValue) const;
      Numeric integrate(const InputValue& value) const;
      Numeric intervallSize() const;
      size_t numberOfIntervalls() const;
      void setFunctionPointer(FunctionType const* function);
    protected:
      Numeric _minValue, _maxValue, _factor;
      InputValue _offset;
      std::vector<Numeric> _table;
      int toGrid(const InputValue& value) const;
      void computeTable(const InputValue& minValue, const InputValue& maxValue, const Numeric& intervallSize);
    };
    template<class Numeric>
      class IntegralLookup2D : public IntegralOverFunction<Numeric, 2>{
    public:
      typedef typename IntegralOverFunction<Numeric, 2>::InputValue InputValue;
      typedef typename IntegralOverFunction<Numeric, 2>::FunctionType FunctionType;
      IntegralLookup2D(FunctionType const* function,  const InputValue& minValue, const InputValue& maxValue, const Numeric& intervallSize);
      Numeric integrate(const InputValue& minValue, const InputValue& maxValue) const;
      Numeric integrate(const InputValue& value) const;
      Numeric intervallSize() const;
      size_t numberOfIntervalls() const;
      void setFunctionPointer(FunctionType const* function);
    protected:
      typedef Eigen::Vector2i Index;
      Numeric _minValue, _maxValue, _factor;
      InputValue _offset;
      std::vector<std::vector<Numeric> > _table;
      Index toGrid(const InputValue& value) const;
      void computeTable(const InputValue& minValue, const InputValue& maxValue, const Numeric& intervallSize);
    };
  };
};

#include "integral_lookup.hpp"

#endif // _TOOLS_INTEGRAL_LOOKUP_H_
