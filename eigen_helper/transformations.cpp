#include "transformations.h"

Eigen::Isometry3f Tools::EigenHelper::toIsometry3f(const Eigen::Isometry2f& pose){
  Eigen::Isometry3f result(Eigen::Isometry3f::Identity());
  result.matrix().block(0,0,2,2) = pose.linear();
  result.translation().x() = pose.translation().x();
  result.translation().y() = pose.translation().y();
  return result;
}

Eigen::Isometry3f Tools::EigenHelper::toIsometry3f(const Eigen::Isometry3d& pose){
  Eigen::Isometry3f result = Eigen::Isometry3f::Identity();
  result.matrix() = pose.matrix().cast<float>();
  return result;
}

Eigen::Isometry3d Tools::EigenHelper::toIsometry3d(const Eigen::Isometry2f& pose){
  Eigen::Isometry3d result;
  result.matrix() = Tools::EigenHelper::toIsometry3f(pose).matrix().cast<double>();
  return result;
}

Eigen::Isometry2f Tools::EigenHelper::toIsometry2f(const Eigen::Isometry3f& pose){
  Eigen::Isometry2f result;
  result.linear() = pose.matrix().block(0,0,2,2);
  result.translation().x() = pose.translation().x();
  result.translation().y() = pose.translation().y();
  return result;
}

Eigen::Isometry2f Tools::EigenHelper::toIsometry2f(const Eigen::Isometry3d& pose){
  Eigen::Isometry3f buff = Tools::EigenHelper::toIsometry3f(pose);
  return Tools::EigenHelper::toIsometry2f(buff);
}
