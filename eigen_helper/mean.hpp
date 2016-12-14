#include <Eigen/Eigenvalues>

#include <iostream>

template<class Numeric, size_t dim>
Eigen::Matrix<Numeric, dim, 1> Tools::EigenHelper::meanTranslation(const std::vector<Eigen::Matrix<Numeric, dim, 1>, Eigen::aligned_allocator<Eigen::Matrix<Numeric, dim, 1> > >& elements,
					       const std::vector<Numeric>& weights){
  std::vector<Numeric> weightsToUse = weights;
  if(weightsToUse.empty()){
    weightsToUse.resize(elements.size(), Numeric(1.0));
  }else if(elements.size() != weightsToUse.size()){
    std::cout << "ERROR in Tools::EigenHelper::meanTranslation: elements and weights have different sizes!" << std::endl;
    return Eigen::Matrix<Numeric, dim, 1>::Zero();
  }
  Numeric weightsSum = 0.0;
  Eigen::Matrix<Numeric, dim, 1> mean(Eigen::Matrix<Numeric, dim, 1>::Zero());
  for(size_t i = 0; i < elements.size(); ++i){
    mean += weightsToUse[i]*elements[i];
    weightsSum += weightsToUse[i];
  }
  if(weightsSum > Numeric(0.0)){
    mean /= weightsSum;
  }
  return mean;
}

template<class Numeric>
Eigen::Matrix<Numeric, 2, 2> Tools::EigenHelper::meanRotation(const std::vector<Eigen::Matrix<Numeric, 2, 2>, Eigen::aligned_allocator<Eigen::Matrix<Numeric, 2, 2> > >& elements,
					  const std::vector<Numeric>& weights){
  //std::vector<Numeric> weightsToUse = weights;
  //if(weightsToUse.empty()){
  //  weightsToUse.resize(elements.size(), Numeric(1.0));
  //}else if(elements.size() != weightsToUse.size()){
  //  std::cout << "ERROR in Tools::EigenHelper::meanRotation: elements and weights have different sizes!" << std::endl;
  //  return Eigen::Matrix<Numeric, 2, 2>::Identity();
  //}
  //Eigen::Matrix<Numeric, 2, 1> mean(Eigen::Matrix<Numeric, 2, 1>::Zero());
  //for(size_t i = 0; i < elements.size(); ++i){
  //  mean += weightsToUse[i]*elements[i].col(0);
  //}
  //mean.normalize();
  //
  //// compute rotation from mean
  //Eigen::Matrix<Numeric, 2, 2> result;
  //result.col(0) = mean;
  //result(0,1) = -mean.y();
  //result(1,1) = mean.x();
  //return result;

  Eigen::Matrix<Numeric, 2, 2> result(Eigen::Matrix<Numeric, 2, 2>::Identity());
  std::vector<Numeric> weightsToUse = weights;
  if(weightsToUse.empty()){
    weightsToUse.resize(elements.size(), Numeric(1.0));
  }else if(elements.size() != weightsToUse.size()){
    std::cout << "ERROR in Tools::EigenHelper::meanRotation: elements and weights have different sizes!" << std::endl;
    return result;
  }

  Eigen::Matrix<Numeric, 4, 4> mean(Eigen::Matrix<Numeric, 4, 4>::Zero()); 
  Eigen::Quaternion<Numeric> q;
  Eigen::Matrix<Numeric, 4, 1> buff;
  Numeric sumWeights = 0.0;

  // add weighted orientations
  for(size_t i = 0; i < elements.size(); ++i){
    sumWeights += weightsToUse[i];
    Eigen::Matrix<Numeric, 3, 3> matrix(Eigen::Matrix<Numeric, 3, 3>::Identity());
    matrix.block(0,0,2,2) = elements[i];
    q = Eigen::Quaternion<Numeric>(matrix);
    buff(0) = q.w();
    buff(1) = q.x();
    buff(2) = q.y();
    buff(3) = q.z();
    mean += weightsToUse[i] * buff*buff.transpose();
  }
  if(sumWeights > Numeric(0.0)){  
    mean /= sumWeights;
  }

  // get mean orientation from matrix mean
  Eigen::EigenSolver<Eigen::Matrix<Numeric, 4, 4> > es(mean);
  int best = -1;
  float max_value = -std::numeric_limits<Numeric>::infinity();
  for(int i = 0; i < es.eigenvalues().size(); ++i){
    if(std::fabs(es.eigenvalues()[i]) > max_value){
      max_value = es.eigenvalues()[i].real();
      best = i;
    }
  }

  if(best == -1){
    std::cerr << "ERROR in Tools::EigenHelper::meanRotation: no best eigenvalue found!" << std::endl;
    return result;
  }

  if(es.eigenvectors().col(best)(0).imag() != 0 ||
     es.eigenvectors().col(best)(1).imag() != 0 ||
     es.eigenvectors().col(best)(2).imag() != 0 ||
     es.eigenvectors().col(best)(3).imag() != 0){
    std::cout << "ERROR in Tools::EigenHelper::meanRotation: eigenvector is complex!" << std::endl;
    return result;
  }
  // mean orientation is valid
  q = Eigen::Quaternion<Numeric>(es.eigenvectors().col(best)(0).real(),
			       es.eigenvectors().col(best)(1).real(),
			       es.eigenvectors().col(best)(2).real(),
			       es.eigenvectors().col(best)(3).real());
  Eigen::Matrix<Numeric, 3, 3> buffResult = q.toRotationMatrix();
  if(buffResult.col(2) != Eigen::Matrix<Numeric, 3, 1>(0.0, 0.0, 1.0) || 
     buffResult.row(2).transpose() != Eigen::Matrix<Numeric, 3, 1>(0.0, 0.0, 1.0) ){
    std::cerr << "ERROR in Tools::EigenHelper::meanRotation: mean of 2D rotation is not a 2D rotation!" << std::endl;
    std::cerr << "3D rotation: " << std::endl << buffResult << std::endl << std::endl;
    return result;
  }
  result = q.toRotationMatrix().block(0,0,2,2);
  return result;
}

template<class Numeric>
Eigen::Matrix<Numeric, 3, 3> Tools::EigenHelper::meanRotation(const std::vector<Eigen::Matrix<Numeric, 3, 3>, Eigen::aligned_allocator<Eigen::Matrix<Numeric, 3, 3> > >& elements,
					  const std::vector<Numeric>& weights=std::vector<Numeric>()){
  Eigen::Matrix<Numeric, 3, 3> result(Eigen::Matrix<Numeric, 3, 3>::Identity());
  std::vector<Numeric> weightsToUse = weights;
  if(weightsToUse.empty()){
    weightsToUse.resize(elements.size(), Numeric(1.0));
  }else if(elements.size() != weightsToUse.size()){
    std::cout << "ERROR in Tools::EigenHelper::meanRotation: elements and weights have different sizes!" << std::endl;
    return result;
  }

  Eigen::Matrix<Numeric, 4, 4> mean(Eigen::Matrix<Numeric, 4, 4>::Zero()); 
  Eigen::Quaternion<Numeric> q;
  Eigen::Vector4f buff;
  Numeric sumWeights = 0.0;

  // add weighted orientations
  for(size_t i = 0; i < elements.size(); ++i){
    sumWeights += weightsToUse[i];
    q = Eigen::Quaternion<Numeric>(elements[i]);
    buff(0) = q.w();
    buff(1) = q.x();
    buff(2) = q.y();
    buff(3) = q.z();
    mean += weightsToUse[i] * buff*buff.transpose();
  }
  if(sumWeights > Numeric(0.0)){  
    mean /= sumWeights;
  }

  // get mean orientation from matrix mean
  Eigen::EigenSolver<Eigen::Matrix<Numeric, 4, 4> > es(mean);
  int best = -1;
  float max_value = -std::numeric_limits<float>::infinity();
  for(int i = 0; i < es.eigenvalues().size(); ++i){
    if(std::fabs(es.eigenvalues()[i]) > max_value){
      max_value = es.eigenvalues()[i].real();
      best = i;
    }
  }

  if(best == -1){
    std::cerr << "ERROR in Tools::EigenHelper::meanRotation: no best eigenvalue found!" << std::endl;
    return result;
  }

  if(es.eigenvectors().col(best)(0).imag() != 0 ||
     es.eigenvectors().col(best)(1).imag() != 0 ||
     es.eigenvectors().col(best)(2).imag() != 0 ||
     es.eigenvectors().col(best)(3).imag() != 0){
    std::cout << "ERROR in Tools::EigenHelper::meanRotation: eigenvector is complex!" << std::endl;
    return result;
  }
  // mean orientation is valid
  q = Eigen::Quaternion<Numeric>(es.eigenvectors().col(best)(0).real(),
			       es.eigenvectors().col(best)(1).real(),
			       es.eigenvectors().col(best)(2).real(),
			       es.eigenvectors().col(best)(3).real());
  result = q.toRotationMatrix();
  return result;
}

template<class Numeric>
Eigen::Transform<Numeric, 2, Eigen::Isometry> Tools::EigenHelper::meanIsometry(const std::vector<Eigen::Transform<Numeric, 2, Eigen::Isometry>, 
												 Eigen::aligned_allocator<Eigen::Transform<Numeric, 2, Eigen::Isometry> > >& elements,
									       const std::vector<Numeric>& weights=std::vector<Numeric>()){
  // split isometry in rotation and translation
  std::vector<Eigen::Matrix<Numeric, 2, 2>, Eigen::aligned_allocator<Eigen::Matrix<Numeric, 2, 2> > > rotations(elements.size());
  std::vector<Eigen::Matrix<Numeric, 2, 1>, Eigen::aligned_allocator<Eigen::Matrix<Numeric, 2, 1> > > translations(elements.size());
  for(size_t i = 0; i < elements.size(); ++i){
    rotations[i] = elements[i].linear().matrix();
    translations[i] = elements[i].translation();
  }
  Eigen::Matrix<Numeric, 2, 2> meanRotationMat = meanRotation<Numeric>(rotations, weights);
  Eigen::Matrix<Numeric, 2, 1> meanTranslationVec = meanTranslation<Numeric, 2>(translations, weights);

  Eigen::Transform<Numeric, 2, Eigen::Isometry> result(Eigen::Transform<Numeric, 2, Eigen::Isometry>::Identity());
  result.matrix().block(0,0,2,2) = meanRotationMat;
  result.translation() = meanTranslationVec;
  return result;
}

template<class Numeric>
Eigen::Transform<Numeric, 3, Eigen::Isometry> Tools::EigenHelper::meanIsometry(const std::vector<Eigen::Transform<Numeric, 3, Eigen::Isometry>, 
												 Eigen::aligned_allocator<Eigen::Transform<Numeric, 3, Eigen::Isometry> > >& elements,
									       const std::vector<Numeric>& weights=std::vector<Numeric>()){
  // split isometry in rotation and translation
  std::vector<Eigen::Matrix<Numeric, 3, 3>, Eigen::aligned_allocator<Eigen::Matrix<Numeric, 3, 3> > > rotations(elements.size());
  std::vector<Eigen::Matrix<Numeric, 3, 1>, Eigen::aligned_allocator<Eigen::Matrix<Numeric, 3, 1> > > translations(elements.size());
  for(size_t i = 0; i < elements.size(); ++i){
    rotations[i] = elements[i].linear().matrix();
    translations[i] = elements[i].translation();
  }
  Eigen::Matrix<Numeric, 3, 3> meanRotationMat = meanRotation<Numeric>(rotations, weights);
  Eigen::Matrix<Numeric, 3, 1> meanTranslationVec = meanTranslation<Numeric, 3>(translations, weights);

  Eigen::Transform<Numeric, 3, Eigen::Isometry> result(Eigen::Transform<Numeric, 3, Eigen::Isometry>::Identity());
  result.matrix().block(0,0,3,3) = meanRotationMat;
  result.translation() = meanTranslationVec;
  return result;
}
