#include "sampler.h"

#include <ctime>


Tools::Sampler::Sampler():
  _uniformDistributionSeedZero(std::time(0)), _uniformDistributionZero(0.0f, 1.0f),
  _uniformDistributionGeneratorZero(_uniformDistributionSeedZero, _uniformDistributionZero),
  _normalDistributionSeed(std::time(0)), _normalDistribution(0.0f, 1.0f),
  _normalDistributionGenerator(_normalDistributionSeed, _normalDistribution)
{

}

Tools::Sampler::~Sampler(){

}


void Tools::Sampler::resample(const std::vector<double>& weights, std::vector<size_t>& indices){
  if(indices.empty()){
    std::cout << "ERROR in Tools::Sampler::resample: number of indices to sample = 0" << std::endl;
    return;
  }
  if(weights.size() == 0){
    std::cout << "ERROR in Tools::Sampler::resample: Nothing to be sampled from, i.e. empty weight distribution!" << std::endl;
    return;
  }

  std::vector<double> distribution(weights.size(),0.0);
  distribution[0] = weights[0];
  for(size_t i = 1; i < weights.size(); ++i){
    distribution[i] = distribution[i-1]+weights[i];
  }

  int maxj = distribution.size()-1;
  double step = 1.0*distribution.back()/indices.size();
  double pointer = step*drand48();//sampleFromUniformDistribution(0.,step);
  int j = 0;
  for(size_t i = 0; i < indices.size(); ++i){
    while(pointer > distribution[j] && j <= maxj){
      j++;
    }
    if(j > maxj){
      std::cout << "error sampling: " << j << " > " << maxj << std::endl;
    }
    indices[i] = std::min(j,maxj);
    pointer += step;
  }
}

float Tools::Sampler::sampleFromUniformDistribution(const float& min_, const float& max_){
  if(min_ >= max_){
    return min_;
  }
  float range = max_ - min_;
  return min_ + range*_uniformDistributionGeneratorZero(); 
}

int Tools::Sampler::sampleIntFromUniformDistribution(const int& min_, const int& max_){
  if(min_ >= max_){
    return min_;
  }
  int range = max_ - min_;
  int result = min_ + range*_uniformDistributionGeneratorZero(); 
  if(result < max_){
    return result;
  }
  return max_-1;
}

float Tools::Sampler::sampleFromNormalDistribution(float mean, float sigma) {
  return mean + sigma*_normalDistributionGenerator();
}

float Tools::Sampler::sampleFromTriangularDistribution(float mean, float width){
  float u = sampleFromUniformDistribution(0.f, 1.f);
  if(u <= 0.5) {
    u = -0.5 + sqrt(u * 0.5);
  } else {
    u = 0.5 - sqrt( (1-u) * 0.5);
  }
  return (u * 2 * width) + mean;
}
