#ifndef _TOOLS_EIGEN_HELPER_MEAN_H_
#define _TOOLS_EIGEN_HELPER_MEAN_H_

#include <Eigen/Geometry>
#include<vector>

namespace Tools{
  namespace EigenHelper{
    template<class Numeric, size_t dim>
      Eigen::Matrix<Numeric, dim, 1> meanTranslation(const std::vector<Eigen::Matrix<Numeric, dim, 1>, Eigen::aligned_allocator<Eigen::Matrix<Numeric, dim, 1> > >&,
						     const std::vector<Numeric>& weights=std::vector<Numeric>());
    template<class Numeric>
      Eigen::Matrix<Numeric, 2, 2> meanRotation(const std::vector<Eigen::Matrix<Numeric, 2, 2>, Eigen::aligned_allocator<Eigen::Matrix<Numeric, 2, 2> > >&,
						  const std::vector<Numeric>& weights=std::vector<Numeric>());
    template<class Numeric>
      Eigen::Matrix<Numeric, 3, 3> meanRotation(const std::vector<Eigen::Matrix<Numeric, 3, 3>, Eigen::aligned_allocator<Eigen::Matrix<Numeric, 3, 3> > >&,
						  const std::vector<Numeric>& weights=std::vector<Numeric>());
    template<class Numeric>
      Eigen::Transform<Numeric, 2, Eigen::Isometry> meanIsometry(const std::vector<Eigen::Transform<Numeric, 2, Eigen::Isometry>, 
								 Eigen::aligned_allocator<Eigen::Transform<Numeric, 2, Eigen::Isometry> > >& elements,
							    const std::vector<Numeric>& weights=std::vector<Numeric>());
    template<class Numeric>
      Eigen::Transform<Numeric, 3, Eigen::Isometry> meanIsometry(const std::vector<Eigen::Transform<Numeric, 3, Eigen::Isometry>, 
								 Eigen::aligned_allocator<Eigen::Transform<Numeric, 3, Eigen::Isometry> > >& elements,
							    const std::vector<Numeric>& weights=std::vector<Numeric>());
  };
};

#include "mean.hpp"

#endif // _TOOLS_EIGEN_HELPER_MEAN_H_
