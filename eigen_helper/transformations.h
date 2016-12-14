#ifndef _TRANSFORMATIONS_H_
#define _TRANSFORMATIONS_H_

#include <Eigen/Core>
#include <Eigen/Geometry>

namespace Tools{
  namespace EigenHelper{
    Eigen::Isometry3f toIsometry3f(const Eigen::Isometry2f& pose);
    Eigen::Isometry3f toIsometry3f(const Eigen::Isometry3d& pose);
    Eigen::Isometry3d toIsometry3d(const Eigen::Isometry2f& pose);
    Eigen::Isometry2f toIsometry2f(const Eigen::Isometry3f& pose);
    Eigen::Isometry2f toIsometry2f(const Eigen::Isometry3d& pose);
  };
};
#endif // _TRANSFORMATIONS_H_
