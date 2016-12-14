#include "eigen_helper/mean.h"

#include "gtest/gtest.h"

TEST(mean, translation) {
  std::vector<Eigen::Vector2f, Eigen::aligned_allocator<Eigen::Vector2f> > elements(4);
  for(size_t i = 0; i < elements.size(); ++i){
    float alpha = i*1.0/elements.size()*M_PI;
    elements[i] = Eigen::Vector2f(cos(alpha), sin(alpha));
  }
  Eigen::Vector2f mean = Tools::EigenHelper::meanTranslation<float, 2>(elements);
  Eigen::Vector2f expectedMean(1, 1+sqrt(2));
  expectedMean *= 0.25;
  EXPECT_NEAR(0.f, (mean-expectedMean).norm(), 1e-10);
}

TEST(mean, rotation2D){
  std::vector<Eigen::Matrix2f, Eigen::aligned_allocator<Eigen::Matrix2f> > elements(5);
  for(size_t i = 0; i < elements.size(); ++i){
    float alpha = i*1.0/(elements.size()-1)*M_PI;
    elements[i] = Eigen::Rotation2D<float>(alpha).matrix();
  }
  Eigen::Matrix2f mean = Tools::EigenHelper::meanRotation<float>(elements);
  Eigen::Matrix2f expectedMean = Eigen::Rotation2D<float>(M_PI/2.f).matrix();
  for(int i = 0; i < mean.rows(); ++i){
    for(int j = 0; j < mean.cols(); ++j){
      EXPECT_NEAR(expectedMean(i,j), mean(i,j), 1e-6);
    }
  }
}

TEST(mean, rotation3D){
  std::vector<Eigen::Matrix3f, Eigen::aligned_allocator<Eigen::Matrix3f> > elements(5);
  for(size_t i = 0; i < elements.size(); ++i){
    float alpha = i*1.0/(elements.size()-1)*M_PI;
    elements[i] = Eigen::AngleAxis<float>(alpha, Eigen::Vector3f::UnitX()).matrix();
  }
  Eigen::Matrix3f mean = Tools::EigenHelper::meanRotation<float>(elements);
  Eigen::Matrix3f expectedMean = Eigen::AngleAxis<float>(M_PI/2.f, Eigen::Vector3f::UnitX()).matrix();
  for(int i = 0; i < mean.matrix().rows(); ++i){
    for(int j = 0; j < mean.matrix().cols(); ++j){
      EXPECT_NEAR(expectedMean.matrix()(i,j), mean.matrix()(i,j), 1e-6);
    }
  }
}

TEST(mean, isometry){
  std::vector<Eigen::Isometry3f, Eigen::aligned_allocator<Eigen::Isometry3f> > elements(5, Eigen::Isometry3f::Identity());
  for(size_t i = 0; i < elements.size(); ++i){
    float alpha = i*1.0/(elements.size()-1)*M_PI;
    elements[i].matrix().block(0,0,3,3) = Eigen::AngleAxis<float>(alpha, Eigen::Vector3f::UnitX()).matrix();
    elements[i].translation() = Eigen::Vector3f(cos(alpha), sin(alpha), 0.f);
  }
  Eigen::Isometry3f mean = Tools::EigenHelper::meanIsometry<float>(elements);
  Eigen::Isometry3f expectedMean(Eigen::Isometry3f::Identity());
  expectedMean.matrix().block(0,0,3,3) = Eigen::AngleAxis<float>(M_PI/2.f, Eigen::Vector3f::UnitX()).matrix();
  expectedMean.translation() = 0.2f*Eigen::Vector3f(0.f, 1+sqrt(2), 0.f);
  for(int i = 0; i < mean.matrix().rows(); ++i){
    for(int j = 0; j < mean.matrix().cols(); ++j){
      EXPECT_NEAR(expectedMean.matrix()(i,j), mean.matrix()(i,j), 1e-6);
    }
  }
}
